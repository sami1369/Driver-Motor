#include <stdio.h>
#include "i2c.h"
#include "hal/i2c_types.h"

I2C::I2C(i2c_port_t port, size_t slav_rx_buf_len, size_t slav_tx_buf_len)
{
    m_port = port;
    m_slav_rx_buf_len = slav_rx_buf_len;
    m_slav_tx_buf_len = slav_tx_buf_len;
}

I2C::~I2C()
{
    i2c_driver_delete(m_port);
}

esp_err_t I2C::initMaster(int sda_io_num, int scl_io_num, uint32_t clk_speed, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_flags)
{
    esp_err_t status = ESP_OK;
    i2c_config_t _config{};

    m_mode = I2C_MODE_MASTER;

    _config.mode = m_mode;
    _config.sda_io_num = sda_io_num;
    _config.scl_io_num = scl_io_num;
    _config.master.clk_speed = clk_speed;
    _config.sda_pullup_en = sda_pullup_en;
    _config.scl_pullup_en = scl_pullup_en;
    _config.clk_flags = clk_flags;

    status |= i2c_param_config(m_port, &_config);

    status |= i2c_driver_install(m_port, m_mode, m_slav_rx_buf_len, m_slav_tx_buf_len, 0);

    return status;
}

uint8_t I2C::readRegister(uint8_t dev_addr, uint8_t reg_addr)
{
    uint8_t rxBuf{};
    i2c_master_write_read_device(m_port, dev_addr, &reg_addr, 1, &rxBuf, 1, pdMS_TO_TICKS(1000));
    
    return rxBuf;
}

esp_err_t I2C::writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t txData)
{
    const uint8_t txBuf[2]{reg_addr, txData};
    
    return i2c_master_write_to_device(m_port, dev_addr, txBuf, 2, pdMS_TO_TICKS(1000));
}
