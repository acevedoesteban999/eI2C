#pragma once
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_FREQ_HZ 400000
#define MAX_TIKS_WAIT 1000
#define MAX_TRY 3    
#define MAX_DELAY_TRY 10

#define EI2C_DEFAULT_GPIO (ei2c_gpio){ \
    .SDA = 22, \
    .SCL = 21, \
    .PORT = I2C_NUM_0  \
}

typedef struct{
    unsigned char SDA;
    unsigned char SCL;
    i2c_port_t PORT;
}ei2c_gpio;

extern ei2c_gpio EI2C_GPIO;

bool ei2c_has_error();

void ei2c_scan(int SDA, int SCL, int I2C_Port);
esp_err_t ei2c_write(uint8_t ADDRESS, uint8_t *data, unsigned len);
void ei2c_set_gpio(ei2c_gpio gpio);
esp_err_t ei2c_master_init();
