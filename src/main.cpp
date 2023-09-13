/*
 *  To play with the 240x240 display module.
 *  Author: Tim Schmidt 2023
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"
#include "esp_log.h"
static const char* TAG = "Display240x240";

#include "driver/i2c.h"
#define I2C_MASTER_SCL_IO           22       /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21       /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0        /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0        /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0        /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000


#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

#include "lvgl.h"


extern "C" {
  void app_main();
}

/*
 * I2C Initialization Code
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        //.master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
      #pragma GCC diagnostic pop
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}



void DrawDisplayPane()
{
  ESP_LOGI(TAG, "Entered DrawDisplayPane()");

  // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003A57), LV_PART_MAIN);

  // lv_obj_t *label = lv_label_create(lv_scr_act());
  // lv_label_set_text(label, "Wolf World!");
  // lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xA41257), LV_PART_MAIN);
  // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}





void app_main()
{
  ESP_LOGI(TAG, "Entered app_main()");
  ESP_LOGI(TAG, "second line");
  DrawDisplayPane();

  ESP_ERROR_CHECK( i2c_master_init() );
  ESP_LOGI(TAG, "I2C Initialized successfully");
}

