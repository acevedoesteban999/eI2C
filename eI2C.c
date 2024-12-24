#include "eI2C.h"

int error_ei2c = -1;


bool ei2c_has_error(){
    return error_ei2c != 0;
}

esp_err_t ei2c_master_init(int SDA, int SCL, int I2C_Port)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA,  
        .scl_io_num = SCL,  
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ, 
    };

    esp_err_t err = i2c_param_config(I2C_Port, &conf);
    if (err != ESP_OK)
        ESP_LOGE("", "I2C param config failed: %s", esp_err_to_name(err));
    else{
        err = i2c_driver_install(I2C_Port, conf.mode, 0, 0, 0);
        if (err != ESP_OK)
            ESP_LOGE("", "I2C driver install failed: %s", esp_err_to_name(err));
    }

    error_ei2c = err;
    return err;
}

void ei2c_scan(int SDA, int SCL, int I2C_Port){
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA,
        .scl_io_num = SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    i2c_param_config(I2C_Port, &conf);
    i2c_driver_install(I2C_Port, conf.mode, 0, 0, 0);
    
    int i;
    esp_err_t err;

    ESP_LOGI("", "Starting I2C scan...");

    for (i = 0x03; i < 0x78; i++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        
        err = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(1000));
        i2c_cmd_link_delete(cmd);

        if (err == ESP_OK) {
            ESP_LOGI("", "I2C => 0x%02x", i);
        } else if (err == ESP_ERR_TIMEOUT) {
            ESP_LOGE("", "I2C bus is busy");
        }
    }

    ESP_LOGI("", "I2C scan completed.");

}

esp_err_t ei2c_write(i2c_port_t I2C_PORT, uint8_t ADDRESS ,uint8_t data_t ,unsigned len){
    if(!ei2c_has_error()){
        esp_err_t err;
        for (int i = 0; i < MAX_TRY; i++) {
            err = i2c_master_write_to_device(I2C_PORT, ADDRESS, data_t, 4, MAX_TIKS_WAIT);
            if (err == ESP_OK) break;
            vTaskDelay(pdMS_TO_TICKS(MAX_DELAY_TRY)); 
        }
        vTaskDelay(pdMS_TO_TICKS(2)); 
        return err;
    }
    return error_ei2c;
}