#pragma once
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_FREQ_HZ 400000          

esp_err_t i2c_master_init(int SDA, int SCL, int I2C_Port);

void i2c_scan(int SDA, int SCL, int I2C_Port);
