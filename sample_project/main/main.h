
#pragma once
#include <string>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "wifi.h"

class Main final
{
private:
public:
    Wifi::state_e wifiState { Wifi::state_e::NOT_INITIALIZED };
    Wifi wifiApp;
    void run(void);
    void setup(void);
};

void Main::run(void)
{
    wifiState = wifiApp.GetState();

    switch (wifiState)
    {
    case Wifi::state_e::READY_TO_CONNECT:
        std::cout << "Wifi Status: READY_TO_CONNECT\n";
        wifiApp.Begin();
        break;
    case Wifi::state_e::DISCONNECTED:
        std::cout << "Wifi Status: DISCONNECTED\n";
        wifiApp.Begin();
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

void Main::setup(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();

    wifiApp.SetCredentials("TP-Link_8020", "50824823");
    wifiApp.Init();
}
