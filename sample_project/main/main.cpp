
#include <string>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "wifi.h"

Wifi::state_e wifiState{Wifi::state_e::NOT_INITIALIZED};
Wifi Wifi;
extern "C" void app_main(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();

    Wifi.SetCredentials("TP-Link_8020", "50824823");
    Wifi.Init();
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));

        wifiState = Wifi.GetState();
        switch (wifiState)
        {
        case Wifi::state_e::READY_TO_CONNECT:
            std::cout << "Wifi Status: READY_TO_CONNECT\n";
            Wifi.Begin();
            break;
        case Wifi::state_e::DISCONNECTED:
            std::cout << "Wifi Status: DISCONNECTED\n";
            Wifi.Begin();
            break;
        case Wifi::state_e::CONNECTING:
            std::cout << "Wifi Status: CONNECTING\n";
            break;
        case Wifi::state_e::WAITING_FOR_IP:
            std::cout << "Wifi Status: WAITING_FOR_IP\n";
            break;
        case Wifi::state_e::ERROR:
            std::cout << "Wifi Status: ERROR\n";
            break;
        case Wifi::state_e::CONNECTED:
            std::cout << "Wifi Status: CONNECTED\n";
            break;
        case Wifi::state_e::NOT_INITIALIZED:
            std::cout << "Wifi Status: NOT_INITIALIZED\n";
            break;
        case Wifi::state_e::INITIALIZED:
            std::cout << "Wifi Status: INITIALIZED\n";
            break;
        }
    }
}

