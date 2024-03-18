#pragma once

#include "driver/gpio.h"

namespace CPPGPIO
{
    class Gpio
    {
    private:
        esp_err_t m_init(const gpio_num_t pin, const bool activeLow);

        gpio_num_t m_pin;
        bool m_active_low;
        int m_level = 0;

    public:
        Gpio(const gpio_num_t pin, const bool activeLow);

        esp_err_t on(void);
        esp_err_t off(void);
        esp_err_t toggle(void);
        esp_err_t setLevel(int level);

    

    }; // GpioBase Class

} // CPPGPIO Namespace
