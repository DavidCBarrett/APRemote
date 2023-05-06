
#include "EnumsToStrings.h"

#define ENUM_TO_STRING(etype, e) case etype::e : return #e;
#define ENUM_TO_USER_CSTR(etype, e, usercstr) case etype::e : return usercstr;

const char* wifi_mode_tToCStr(wifi_mode_t e) noexcept
{
    switch (e)
    {
	    ENUM_TO_USER_CSTR (wifi_mode_t, WIFI_MODE_NULL, "NULL")
	    ENUM_TO_USER_CSTR (wifi_mode_t, WIFI_MODE_STA, "STA")
	    ENUM_TO_USER_CSTR (wifi_mode_t, WIFI_MODE_AP, "AP")
	    ENUM_TO_USER_CSTR (wifi_mode_t, WIFI_MODE_APSTA, "APSTA")
	    ENUM_TO_USER_CSTR (wifi_mode_t, WIFI_MODE_MAX, "MAX")
    }
    return "wifi_mode_tToCStr out of range";
}

const char* WiFiEvent_tToString(WiFiEvent_t e) noexcept
{
    switch (e)
    {
	  ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_READY)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_SCAN_DONE)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_START)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_STOP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_CONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_DISCONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_GOT_IP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_GOT_IP6)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_STA_LOST_IP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_START)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_STOP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_STACONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_AP_GOT_IP6)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WIFI_FTM_REPORT)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_START)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_STOP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_CONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_DISCONNECTED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_GOT_IP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_ETH_GOT_IP6)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WPS_ER_SUCCESS)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WPS_ER_FAILED)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WPS_ER_TIMEOUT)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WPS_ER_PIN)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_WPS_ER_PBC_OVERLAP)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_SC_SCAN_DONE)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_SC_FOUND_CHANNEL)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_SC_GOT_SSID_PSWD)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_SC_SEND_ACK_DONE)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_INIT)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_DEINIT)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_START)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_END)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_CRED_RECV)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_CRED_FAIL)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_PROV_CRED_SUCCESS)
      ENUM_TO_STRING (WiFiEvent_t, ARDUINO_EVENT_MAX)
    }
    return "WiFiEvent_tToString out of range";
}

const char* wifi_err_reason_tToString(wifi_err_reason_t e) noexcept
{
    switch (e)
    {
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_UNSPECIFIED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AUTH_EXPIRE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AUTH_LEAVE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ASSOC_EXPIRE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ASSOC_TOOMANY)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NOT_AUTHED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NOT_ASSOCED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ASSOC_LEAVE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ASSOC_NOT_AUTHED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_DISASSOC_PWRCAP_BAD)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_DISASSOC_SUPCHAN_BAD)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_BSS_TRANSITION_DISASSOC)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_IE_INVALID)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_MIC_FAILURE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_IE_IN_4WAY_DIFFERS)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_GROUP_CIPHER_INVALID)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_PAIRWISE_CIPHER_INVALID)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AKMP_INVALID)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_UNSUPP_RSN_IE_VERSION)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_INVALID_RSN_IE_CAP)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_802_1X_AUTH_FAILED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_CIPHER_SUITE_REJECTED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_TDLS_PEER_UNREACHABLE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_TDLS_UNSPECIFIED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_SSP_REQUESTED_DISASSOC)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NO_SSP_ROAMING_AGREEMENT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_BAD_CIPHER_OR_AKM)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NOT_AUTHORIZED_THIS_LOCATION)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_SERVICE_CHANGE_PERCLUDES_TS)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_UNSPECIFIED_QOS)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NOT_ENOUGH_BANDWIDTH)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_MISSING_ACKS)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_EXCEEDED_TXOP)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_STA_LEAVING)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_END_BA)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_UNKNOWN_BA)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_TIMEOUT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_PEER_INITIATED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AP_INITIATED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_INVALID_FT_ACTION_FRAME_COUNT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_INVALID_PMKID)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_INVALID_MDE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_INVALID_FTE)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_TRANSMISSION_LINK_ESTABLISH_FAILED)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ALTERATIVE_CHANNEL_OCCUPIED)

      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_BEACON_TIMEOUT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_NO_AP_FOUND)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AUTH_FAIL)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ASSOC_FAIL)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_HANDSHAKE_TIMEOUT)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_CONNECTION_FAIL)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_AP_TSF_RESET)
      ENUM_TO_STRING (wifi_err_reason_t, WIFI_REASON_ROAMING)
    }
    return "wifi_err_reason_t out of range";
}