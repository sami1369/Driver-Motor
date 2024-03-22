#include "DRV2605.h"

DRV2605::DRV2605(I2C *i2c)
{
    m_i2c = i2c;
}

void DRV2605::writeByteData(uint8_t dev_addr, uint8_t reg, uint8_t value)
{
    m_i2c->writeRegister( DRV2605_ADDR,reg, value);
}


int DRV2605::readByteData(uint8_t dev_addr, uint8_t reg ){
    return m_i2c->readRegister(DRV2605_ADDR, reg);
}