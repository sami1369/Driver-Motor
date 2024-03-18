
#include "gpio.h"
extern "C" void app_main(void)
{
    CPPGPIO::Gpio Led { GPIO_NUM_2, 0 };
    Led.on();
    while (true)
    {
    }    
}
