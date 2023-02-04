#pragma once

#include <esp_err.h>
#include "esphome/core/log.h"

const char *decode_esp_result(esp_err_t result);
void check_esp_result(esp_err_t result, const char *operation);