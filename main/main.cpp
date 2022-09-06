// SPDX: MIT
// Copyright 2021 Brian Starkey <stark3y@gmail.com>
// Portions from lvgl example: https://github.com/lvgl/lv_port_esp32/blob/master/main/main.c

#include <Arduino.h>
#include <sdkconfig.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <axp192.h>
#include <lvgl.h>
#include <lvgl_helpers.h>
#include <esp_log.h>
#include <i2c_manager.h>

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


[[noreturn]] void mainTask(void *parameter) {

    (void) parameter;

    initArduino();
    
    Serial.setRxTimeout(1);
	Serial.begin(115200, SERIAL_8N1, 3, 1, false, 1, 112);


	i2c_manager_init(I2C_NUM_0);
	
	axp.read = &i2c_manager_read;
	axp.write = i2c_manager_write;
    axp.handle = I2C_NUM_0;

    axp192_init(&axp);

	axp192_ioctl(&axp, AXP192_COULOMB_COUNTER_ENABLE);

	
	set_led(AXP192_HIGH);

	axp192_ioctl(&axp, AXP192_GPIO4_SET_LEVEL, AXP192_HIGH);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	axp192_ioctl(&axp, AXP192_GPIO4_SET_LEVEL, AXP192_LOW);
	vTaskDelay(100 / portTICK_PERIOD_MS);


    lvgl_i2c_locking(i2c_manager_locking());
	lv_init();
	lvgl_interface_init();
	lvgl_display_gpios_init();
	touch_driver_init();

	static lv_disp_draw_buf_t disp_buf;
	size_t display_buffer_size = lvgl_get_display_buffer_size();
	auto* buf1 = (lv_color_t *) heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
	auto* buf2 = (lv_color_t *) heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, display_buffer_size);

	static lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.flush_cb = disp_driver_flush;
	disp_drv.hor_res = 320u;
	disp_drv.ver_res = 240u;
	disp_drv.draw_buf = &disp_buf;
	lv_disp_drv_register(&disp_drv);

	static lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.read_cb = touch_driver_read;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	lv_indev_drv_register(&indev_drv);

	disp_driver_init(&disp_drv);
	
	ui_init();

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

    int i = 0;
	while (true) {
        if(i<10) {
            i++;
        } else {
            i=0;

            float vacin, iacin, vvbus, ivbus, temp, vts, pbat, vbat, icharge, idischarge, vaps, cbat;

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

            lv_label_set_text(ui_labelCharge, (String(icharge*1000)+" mA").c_str());
            lv_label_set_text(ui_labelDischarge, (String(idischarge*1000)+" mA").c_str());
            lv_label_set_text(ui_labelVoltage, (String(vbat)+" V").c_str());
            lv_label_set_text(ui_labelVbus, (String(vacin)+" V").c_str());
            lv_label_set_text(ui_labelIbus, (String(iacin*1000)+" mA").c_str());
        }
        
		lv_task_handler();

		vTaskDelay(30 / portTICK_PERIOD_MS);
	}
}

extern "C" void app_main() 
{
	xTaskCreatePinnedToCore(mainTask, "mainTask", 8192, nullptr, 10, nullptr, APP_CPU_NUM);
}
