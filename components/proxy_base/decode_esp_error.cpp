#include "decode_esp_error.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

const char *decode_esp_error(esp_err_t error)
{
    switch (error)
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