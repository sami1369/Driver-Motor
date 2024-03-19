#pragma once

#include "driver/gpio.h"


    class Gpio
    {
    private:        
        gpio_num_t m_pin;
        gpio_mode_t m_gpio_mode;
        bool m_active_low;
        int m_level = 0;

    public:
        Gpio(const gpio_num_t pin, const bool activeLow, const gpio_mode_t gpio_mode);

        esp_err_t on(void);
        esp_err_t off(void);
        esp_err_t toggle(void);
        int       read(void);

        esp_err_t setLevel(int level);

    

    }; // GpioBase Class

