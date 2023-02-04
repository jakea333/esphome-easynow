#include "decode_esp_result.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "esphome/core/component.h"

const char *decode_esp_result(esp_err_t result)
{
    switch (result)
    {
    case ESP_ERR_ESPNOW_BASE:
        return "ESP_ERR_ESPNOW_BASE";
    case ESP_ERR_ESPNOW_NOT_INIT:
        return "ESP_ERR_ESPNOW_NOT_INIT";
    case ESP_ERR_ESPNOW_ARG:
        return "ESP_ERR_ESPNOW_ARG";
    case ESP_ERR_ESPNOW_NO_MEM:
        return "ESP_ERR_ESPNOW_NO_MEM";
    case ESP_ERR_ESPNOW_FULL:
        return "ESP_ERR_ESPNOW_FULL";
    case ESP_ERR_ESPNOW_NOT_FOUND:
        return "ESP_ERR_ESPNOW_NOT_FOUND";
    case ESP_ERR_ESPNOW_INTERNAL:
        return "ESP_ERR_ESPNOW_INTERNAL";
    case ESP_ERR_ESPNOW_EXIST:
        return "ESP_ERR_ESPNOW_EXIST";
    case ESP_ERR_ESPNOW_IF:
        return "ESP_ERR_ESPNOW_IF";
    case ESP_OK:
        return "ESP_OK";
    case ESP_ERR_WIFI_NOT_INIT:
        return "ESP_ERR_WIFI_NOT_INIT";
    case ESP_ERR_INVALID_ARG:
        return "ESP_ERR_INVALID_ARG";
    case ESP_ERR_NO_MEM:
        return "ESP_ERR_NO_MEM";
    case ESP_ERR_WIFI_CONN:
        return "ESP_ERR_WIFI_CONN";
    case ESP_FAIL:
        return "ESP_FAIL";
    default:
        return "(UNKNOWN ERROR)";
    }
}

void check_esp_result(esp_err_t result, const char *operation)
{
    if (result == ESP_OK)
    {
        ESP_LOGD("CHECKESPESULT", "%s - OK", operation);
    }
    else
    {
        ESP_LOGD("CHECKESPESULT", "%s - Failed %d - %s", operation, result, decode_esp_result(result));
    }
}