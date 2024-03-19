#include "gpio.h"
#include "driver/gpio.h"

Gpio::Gpio(const gpio_num_t pin, const bool activeLow, const gpio_mode_t gpio_mode)
{

    m_pin = pin;
    m_active_low = activeLow;
    m_gpio_mode = gpio_mode;

    gpio_config_t cfg;
    cfg.pin_bit_mask = 1ULL << m_pin;
    cfg.mode = m_gpio_mode;
    cfg.pull_up_en = GPIO_PULLUP_DISABLE;
    cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
    cfg.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&cfg);
}

esp_err_t Gpio::on(void)
{
    m_level = true;
    return gpio_set_level(m_pin, m_active_low ? 0 : 1);
}

esp_err_t Gpio::off(void)
{
    m_level = false;
    return gpio_set_level(m_pin, m_active_low ? 0 : 1);
}

esp_err_t Gpio::toggle(void)
{
    m_level = m_level ? 0 : 1;
    return gpio_set_level(m_pin, m_active_low ? 0 : 1);
}

esp_err_t Gpio::setLevel(int level)
{
    m_level = m_active_low ? !level : level;
    return gpio_set_level(m_pin, m_level);
}

int Gpio::read(void)
{
    return m_active_low ? !gpio_get_level(m_pin) : gpio_get_level(m_pin);
}
