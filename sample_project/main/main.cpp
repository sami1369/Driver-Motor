
#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"




extern "C" void app_main(void)
{
    Gpio *led1, *key1; 
    led1 = new Gpio{GPIO_NUM_2, false, GPIO_MODE_OUTPUT};
    key1= new Gpio{GPIO_NUM_15, false, GPIO_MODE_INPUT};
    
    while (true)
    {
        led1->setLevel(key1->read());
    }
}
