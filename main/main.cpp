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


#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_vfs_fat.h"

#include <sys/stat.h>

extern "C" {
    #include <ui.h>
}


#define LV_TICK_PERIOD_MS 5
/*
#define PIN_NUM_MOSI 23
#define PIN_NUM_MISO 38
#define PIN_NUM_CLK 18
#define PIN_NUM_CS 4
#define DMA_CHANNEL 2
#define MAX_BUFSIZE (16 * 1024)

#define MOUNT_POINT "/sdcard"

static const char *TAG = "SDCARD";*/

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

/*
void test_sd_card(void)
{

    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");


	spi_device_interface_config_t spi_device_conf = {
		.spics_io_num = (gpio_num_t) PIN_NUM_CLK,
	};
	spi_bus_add_device(HSPI_HOST, &spi_device_conf);
    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    ESP_LOGI(TAG, "Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num =  (gpio_num_t) PIN_NUM_MOSI,
        .miso_io_num =  (gpio_num_t) PIN_NUM_MISO,
        .sclk_io_num =  (gpio_num_t) PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(HSPI_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = (gpio_num_t) PIN_NUM_CS;
    slot_config.host_id = HSPI_HOST;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

    // Use POSIX and C standard library functions to work with files.

    // First create a file.
    const char *file_hello = MOUNT_POINT"/hello.txt";

    ESP_LOGI(TAG, "Opening file %s", file_hello);
    FILE *f = fopen(file_hello, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, "Hello %s!\n", card->cid.name);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    const char *file_foo = MOUNT_POINT"/foo.txt";

    // Check if destination file exists before renaming
    struct stat st;
    if (stat(file_foo, &st) == 0) {
        // Delete it if it exists
        unlink(file_foo);
    }

    // Rename original file
    ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
    if (rename(file_hello, file_foo) != 0) {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }

    // Open renamed file for reading
    ESP_LOGI(TAG, "Reading file %s", file_foo);
    f = fopen(file_foo, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    // Read a line from file
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);

    // Strip newline
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);

    // All done, unmount partition and disable SPI peripheral
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Card unmounted");

    //deinitialize the bus after all devices are removed
    spi_bus_free(HSPI_HOST);
}
*/


void mainTask(void *parameter) {

    initArduino();
	Serial.begin(2000000);

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

	axp192_ioctl(&axp, AXP192_COULOMB_COUNTER_ENABLE);

	float vacin, iacin, vvbus, ivbus, temp, vts, pbat, vbat, icharge, idischarge, vaps, cbat;

	/* All ADC registers will be read as floats. */
	axp192_read(&axp, AXP192_ACIN_VOLTAGE, &vacin);
	axp192_read(&axp, AXP192_ACIN_CURRENT, &iacin);
	axp192_read(&axp, AXP192_VBUS_VOLTAGE, &vvbus);
	axp192_read(&axp, AXP192_VBUS_CURRENT, &ivbus);
	axp192_read(&axp, AXP192_TEMP, &temp);
	axp192_read(&axp, AXP192_TS_INPUT, &vts);
	axp192_read(&axp, AXP192_BATTERY_POWER, &pbat);
	axp192_read(&axp, AXP192_BATTERY_VOLTAGE, &vbat);
	axp192_read(&axp, AXP192_CHARGE_CURRENT, &icharge);
	axp192_read(&axp, AXP192_DISCHARGE_CURRENT, &idischarge);
	axp192_read(&axp, AXP192_APS_VOLTAGE, &vaps);
	axp192_read(&axp, AXP192_COULOMB_COUNTER, &cbat);

	printf(
		"vacin: %.2fV iacin: %.2fA vvbus: %.2fV ivbus: %.2fA vts: %.2fV temp: %.0fC "
		"pbat: %.2fmW vbat: %.2fV icharge: %.2fA idischarge: %.2fA, vaps: %.2fV cbat: %.2fmAh",
		vacin, iacin, vvbus, ivbus, vts, temp, pbat, vbat, icharge, idischarge, vaps, cbat
	);
	
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

	////test_sd_card();

	while (true) {
		vTaskDelay(1 / portTICK_PERIOD_MS);
		lv_task_handler();
	}

}

extern "C" void app_main() 
{
	xTaskCreatePinnedToCore(mainTask, "mainTask", 8192, nullptr, 10, nullptr, APP_CPU_NUM);
}
