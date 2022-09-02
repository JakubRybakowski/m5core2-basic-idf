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

axp192_t axp;

static void lv_tick_task(void *arg)
{
	(void) arg;
	lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void set_led(bool on)
{
	axp192_ioctl(&axp, AXP192_GPIO1_SET_LEVEL, on);
}

void mainTask(void *parameter) {

	static i2c_port_t i2c_port = I2C_NUM_1;

	i2c_init(i2c_port);
	
	axp.read = &i2c_read;
	axp.write = &i2c_write;
    axp.handle = &i2c_port;

	axp192_ioctl(&axp, AXP192_DCDC1_SET_VOLTAGE, 3300); //MCU
	axp192_ioctl(&axp, AXP192_DCDC1_ENABLE);

	axp192_ioctl(&axp, AXP192_DCDC3_SET_VOLTAGE, 2800); //BACKLIGHT
	axp192_ioctl(&axp, AXP192_DCDC3_ENABLE);

	axp192_ioctl(&axp, AXP192_LDO2_SET_VOLTAGE, 3300); //PERIPHERAL
	axp192_ioctl(&axp, AXP192_LDO2_ENABLE);

	axp192_ioctl(&axp, AXP192_LDO3_SET_VOLTAGE, 2000); //MOTOR
	axp192_ioctl(&axp, AXP192_LDO3_DISABLE);

	axp192_ioctl(&axp, AXP192_LDOIO0_SET_VOLTAGE, 3300); //ONBOARD 5V
	axp192_ioctl(&axp, AXP192_GPIO0_SET_LEVEL, AXP192_LOW); 
	axp192_ioctl(&axp, AXP192_EXTEN_DISABLE);
	
	set_led(AXP192_HIGH);

	axp192_ioctl(&axp, AXP192_GPIO4_SET_LEVEL, AXP192_HIGH);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	axp192_ioctl(&axp, AXP192_GPIO4_SET_LEVEL, AXP192_LOW);
	vTaskDelay(100 / portTICK_PERIOD_MS);

	lv_init();
	lvgl_interface_init();
	lvgl_display_gpios_init();
	touch_driver_init();

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
		vTaskDelay(1 / portTICK_PERIOD_MS);
		lv_task_handler();
	}

}

extern "C" void app_main() 
{
    initArduino();
	xTaskCreatePinnedToCore(mainTask, "mainTask", 8192, nullptr, 10, nullptr, APP_CPU_NUM);
}
