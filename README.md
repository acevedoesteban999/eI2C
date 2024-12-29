# eI2C

The eI2C module is an implementation of I2C communication for the ESP32. This module allows communication between the ESP32 and other I2C devices, such as sensors and actuators.

## Features

- Support for multiple I2C devices.
- Flexible configuration of the I2C bus speed.
- Error handling and recovery.

## Main Functions

- `ei2c_master_init(int SDA, int SCL, int I2C_Port)`: Initializes the I2C bus in master mode.
- `ei2c_scan(int SDA, int SCL, int I2C_Port)`: Scans for I2C devices on the bus.
- `ei2c_write(i2c_port_t I2C_PORT, uint8_t ADDRESS, uint8_t data_t, unsigned len)`: Writes data to an I2C device.

## Example Usage

```c
#include "eI2C.h"

void app_main() {
    // Initialize the I2C bus
    ei2c_master_init(GPIO_NUM_21, GPIO_NUM_22, I2C_NUM_0);

    // Scan for I2C devices
    ei2c_scan(GPIO_NUM_21, GPIO_NUM_22, I2C_NUM_0);

    // I2C device address
    uint8_t device_address = 0x40;

    // Write data to the device
    uint8_t write_data[2] = {0x01, 0x02};
    ei2c_write(I2C_NUM_0, device_address, write_data, 2);
}
```
