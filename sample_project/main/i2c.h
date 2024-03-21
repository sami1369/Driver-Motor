#pragma once

#include "driver/i2c.h"
#include "esp_intr_alloc.h"

class I2C
{
private:
    i2c_port_t  m_port{};
    i2c_mode_t  m_mode{};
    size_t      m_slav_rx_buf_len{};
    size_t      m_slav_tx_buf_len{};

public:
    I2C(i2c_port_t port, size_t slav_rx_buf_len = 0, size_t slav_tx_buf_len = 0);
    ~I2C();

    esp_err_t   initMaster(int sda_io_num,
                         int scl_io_num,
                         uint32_t clk_speed,
                         bool sda_pullup_en = false,
                         bool scl_pullup_en = false,
                         uint32_t clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL);

    uint8_t     readRegister(uint8_t dev_addr, uint8_t reg_addr);
    esp_err_t   writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t txData);
};