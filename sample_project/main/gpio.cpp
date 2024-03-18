#include "gpio.h"
#include "driver/gpio.h"

namespace CPPGPIO
{
    esp_err_t Gpio::m_init(const gpio_num_t pin, const bool activeLow)
    {
        esp_err_t status{ESP_OK};

        m_pin = pin;
        m_active_low = activeLow;

        gpio_config_t cfg;
        cfg.pin_bit_mask = 1ULL << pin;
        cfg.mode = GPIO_MODE_OUTPUT;
        cfg.pull_up_en = GPIO_PULLUP_DISABLE;
        cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        cfg.intr_type = GPIO_INTR_DISABLE;

        status |= gpio_config(&cfg);

        return status;
    }

    Gpio::Gpio(const gpio_num_t pin, const bool activeLow)
    {
        m_init(pin, activeLow);
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

} // Namespace CPPGPIO