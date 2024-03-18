#include <stdio.h>

#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

extern "C" void app_main(void)
{
    CPPGPIO::Gpio Led{GPIO_NUM_2, 0};
    Led.on();
    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
