#pragma once
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_FREQ_HZ 400000
#define MAX_TIKS_WAIT 1000
#define MAX_TRY 3    
#define MAX_DELAY_TRY 10


void ei2c_scan(int SDA, int SCL, int I2C_Port);
esp_err_t ei2c_write(i2c_port_t I2C_PORT, uint8_t ADDRESS, uint8_t *data, unsigned len);
esp_err_t ei2c_master_init(int SDA, int SCL, int I2C_Port);
