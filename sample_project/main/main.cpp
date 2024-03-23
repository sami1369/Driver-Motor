#include "main.h"
#include "mqtt_client.h"
#include "esp_log.h" //log out put, do not use printf everywhere

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
static const char *TAG = "MQTT ";
// here esp_mqtt_event_handle_t is a struct which receieves struct event from mqtt app start funtion
static void mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    // making obj client of struct esp_mqtt_client_handle_t and assigning it the receieved event client
    esp_mqtt_client_handle_t client = event->client; 
    if (event->event_id == MQTT_EVENT_CONNECTED)
    {
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        esp_mqtt_client_subscribe(client, "LEDon", 0); // in mqtt we require a topic to subscribe and client is from event client and 0 is quality of service it can be 1 or 2
        ESP_LOGI(TAG, "sent subscribe successful");
    }
    else if (event->event_id == MQTT_EVENT_DISCONNECTED)
    {
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED"); // if disconnected
    }
    else if (event->event_id == MQTT_EVENT_SUBSCRIBED)
    {
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
    }
    else if (event->event_id == MQTT_EVENT_UNSUBSCRIBED) // when subscribed
    {
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
    }
    else if (event->event_id == MQTT_EVENT_DATA) // when unsubscribed
    {
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
    }
    else if (event->event_id == MQTT_EVENT_ERROR) // when any error
    {
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
    }
}