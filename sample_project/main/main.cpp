#include "main.h"

Main App;

extern "C" void app_main(void)
{
    App.setup();

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));
        App.run();
    }
}
