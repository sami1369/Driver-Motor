#include "main.h"
#include "freertos/FreeRTOS.h" //it is important too if you want to run mqtt task independently and provides threads funtionality
#include "freertos/task.h"     //MQTT communication often involves asynchronous operations, and FreeRTOS helps handle those tasks effectively
#include "esp_log.h"           //log out put, do not use printf everywhere
#include "mqtt_client.h" //provides important functions to connect with MQTT
#include "esp_event.h"
#define BROKER_URL "mqtt://login:aio_xxx@io.adafruit.com"
#define IO_TOPIC "Sami1990/feeds/LED"
Main AppWifi;
static const char *TAG = "mqtt_example";

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    int msg_id;

    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        // msg_id = esp_mqtt_client_publish(event->client, "Sami1990/Feeds/LED", "11", 0, 1, 0);

        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        break;

    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;

    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

extern "C" void app_main(void)
{
    esp_mqtt_client_handle_t client;
    esp_err_t error;
    AppWifi.setup();
    vTaskDelay(pdMS_TO_TICKS(1000));
    // MQTT config
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.uri = "use your broker";
    mqtt_cfg.port = 1883;
    mqtt_cfg.event_handle = mqtt_event_handler;
    mqtt_cfg.username = "username in adafruit io";
    mqtt_cfg.password = "key generated in Adafruit";
    client = esp_mqtt_client_init(&mqtt_cfg);
    error = esp_mqtt_client_start(client);
    ESP_LOGI(TAG, "Client cond %d", error);

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));
        AppWifi.run();

        client = esp_mqtt_client_init(&mqtt_cfg);
        error = esp_mqtt_client_start(client);
        ESP_LOGI(TAG, "Client cond %d", error);
        esp_mqtt_client_publish(client, "Sami1990/feeds/LED", "1", 0, 1, 0);

        // AppMqtt.run();
    }
}