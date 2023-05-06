//
// Convert various enums to strings for output. would of used https://github.com/Neargye/magic_enum/releases?page=2 but needs c++ compiler V17 or higher
// As an alternative took inspiration from https://belaycpp.com/2021/08/24/best-ways-to-convert-an-enum-to-a-string/
//

#pragma once

#include <WiFiType.h>
#include <WiFiGeneric.h>

extern const char* wifi_mode_tToCStr(wifi_mode_t e) noexcept;

extern const char* WiFiEvent_tToString(WiFiEvent_t e) noexcept;

extern const char* wifi_err_reason_tToString(wifi_err_reason_t e) noexcept;
