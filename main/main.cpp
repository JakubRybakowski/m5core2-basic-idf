// SPDX: MIT
// Copyright 2021 Brian Starkey <stark3y@gmail.com>
// Portions from lvgl example: https://github.com/lvgl/lv_port_esp32/blob/master/main/main.c

#include <Arduino.h>
#include <stdio.h>
#include <sdkconfig.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_spi_flash.h>

#include <axp192.h>
#include <i2c_helper.h>

#include <lvgl.h>
#include <lvgl_helpers.h>


extern "C" {
    #include <ui.h>
}

#define LV_TICK_PERIOD_MS 5

const axp192_t axp = {
	.read = &i2c_read,
	.write = &i2c_write,
};

static void set_led(const axp192_t *axp, bool on);

enum toggle_id {
	TOGGLE_LED = 0,
	TOGGLE_VIB,
	TOGGLE_5V,
};

static void lv_tick_task(void *arg)
{
	(void) arg;

	lv_tick_inc(LV_TICK_PERIOD_MS);
}


static void set_axp192_gpio_012(const axp192_t *axp, int gpio, bool low)
{
	if ((gpio < 0) || (gpio > 2)) {
		return;
	}

	uint8_t val = 0;
	axp192_read_reg(axp, AXP192_GPIO20_SIGNAL_STATUS, &val);

	uint8_t mask = (1 << gpio);
	if (low) {
		val &= ~mask;
	} else {
		val |= mask;
	}

	axp192_write_reg(axp, AXP192_GPIO20_SIGNAL_STATUS, val);
}

static void set_axp192_gpio_34(const axp192_t *axp, int gpio, bool low)
{
	if ((gpio < 3) || (gpio > 4)) {
		return;
	}

	uint8_t val = 0;
	axp192_read_reg(axp, AXP192_GPIO40_SIGNAL_STATUS, &val);

	uint8_t mask = (1 << (gpio - 3));
	if (low) {
		val &= ~mask;
	} else {
		val |= mask;
	}

	axp192_write_reg(axp, AXP192_GPIO40_SIGNAL_STATUS, val);
}

static void set_led(const axp192_t *axp, bool on)
{
	set_axp192_gpio_012(axp, 1, on);
}


void mainTask(void *parameter) {

	lv_init();
	lvgl_interface_init();
	lvgl_display_gpios_init();
	touch_driver_init();
	
	struct rail_entry {
		const char *name;
		axp192_rail_t rail;
		uint16_t millivolts;
	};

	struct rail_entry rails[] = {
		{ "DCDC1 (MCU_VDD)",  AXP192_RAIL_DCDC1, 3300 },
		{ "DCDC3 (LCD_BL)",   AXP192_RAIL_DCDC3, 2800 },
		{ "LDO2 (PERI_VDD)",  AXP192_RAIL_LDO2,  3300 },
		{ "LDO3 (VIB_MOTOR)", AXP192_RAIL_LDO3,  2000 },
	};

	for (int i = 0; i < sizeof(rails) / sizeof(rails[0]); i++) {
		bool enabled;
		uint16_t millivolts;
		axp192_err_t err = axp192_get_rail_millivolts(&axp, rails[i].rail, &millivolts);
		if (err != AXP192_ERROR_OK) {
			printf("%s: get failed\n", rails[i].name);
			continue;
		}

		enabled = false;
		err = axp192_get_rail_state(&axp, rails[i].rail, &enabled);
		if (err != AXP192_ERROR_OK) {
			printf("%s: get state failed\n", rails[i].name);
			continue;
		}

		printf("%s: get %d mV (%s)\n", rails[i].name, millivolts, enabled ? "enabled" : "disabled");

		err = axp192_set_rail_millivolts(&axp, rails[i].rail, rails[i].millivolts);
		if (err != AXP192_ERROR_OK) {
			printf("%s: set failed\n", rails[i].name);
			continue;
		}

		printf("%s: set %d mV\n", rails[i].name, rails[i].millivolts);
	}
	
	axp192_write_reg(&axp, AXP192_CHARGE_CONTROL_1, 0xC1);
	axp192_write_reg(&axp, AXP192_CHARGE_CONTROL_2, 0x41);

	float volts;
	axp192_read(&axp, AXP192_BATTERY_VOLTAGE, &volts);
	printf("Battery voltage: %.2f volts\n", volts);


	axp192_write_reg(&axp, AXP192_GPIO1_CONTROL, 0);
	axp192_write_reg(&axp, AXP192_GPIO2_CONTROL, 0);
	axp192_write_reg(&axp, AXP192_GPIO40_FUNCTION_CONTROL, (1 << 7) | (1 << 2) | (1 << 0));
	axp192_write_reg(&axp, AXP192_PEK, (1 << 6) | (0 << 4) | (1 << 3) | (1 << 2) | (0 << 0));
	axp192_write_reg(&axp, AXP192_BATTERY_CHARGE_CONTROL, (1 << 7) | (1 << 5) | (0 << 0));
	
	axp192_set_rail_state(&axp, AXP192_RAIL_DCDC3, true);
	axp192_set_rail_state(&axp, AXP192_RAIL_LDO2, true);

	set_led(&axp, true);

	set_axp192_gpio_34(&axp, 4, true);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	set_axp192_gpio_34(&axp, 4, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);

	size_t display_buffer_size = lvgl_get_display_buffer_size();

	auto* buf1 = (lv_color_t *) heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
	auto* buf2 = (lv_color_t *) heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);

	static lv_disp_draw_buf_t disp_buf;
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, display_buffer_size);

	static lv_disp_drv_t disp_drv;
	
	lv_disp_drv_init(&disp_drv);
	disp_drv.flush_cb = disp_driver_flush;
	disp_drv.hor_res = 320u;
	disp_drv.ver_res = 240u;
	disp_drv.draw_buf = &disp_buf;
	lv_disp_drv_register(&disp_drv);

	disp_driver_init(&disp_drv);
	

	ui_init();
	
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.read_cb = touch_driver_read;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	lv_indev_drv_register(&indev_drv);

	esp_timer_handle_t periodic_timer;

	const esp_timer_create_args_t periodic_timer_args = {
		.callback = &lv_tick_task,
		.arg = nullptr,
		.dispatch_method = ESP_TIMER_TASK,
		.name = "periodic_gui",
		.skip_unhandled_events = false,
	};

	esp_timer_create(&periodic_timer_args, &periodic_timer);
	esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000);

	while (true) {
		vTaskDelay(5 / portTICK_PERIOD_MS);

		lv_task_handler();
	}

}

extern "C" void app_main() 
{
    initArduino();
	xTaskCreatePinnedToCore(mainTask, "mainTask", 8192, nullptr, 10, nullptr, APP_CPU_NUM);

}
