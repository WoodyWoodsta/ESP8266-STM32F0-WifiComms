/**
* ============================================================================
* File Name          : strings_res.c
* Description        : Source file for all strings used throughout the
*                      project
* Author             : Sean Wood
* ============================================================================
*/

// == Includes ==
#include "strings_res.h"

// == Exported Variables ==

// Strings to send
const uint8_t txString_ATCommandTest[] = "AT\r\n";
const uint8_t txString_ATE0[] = "ATE0\r\n";
const uint8_t txString_stationMode3[] = "AT+CWMODE=3\r\n";
const uint8_t txString_multiConnect1[] = "AT+CIPMUX=1\r\n";
const uint8_t txString_OKReceived[] = "OK Received!\r\n";
const uint8_t txString_ATCommandTestError[] = "AT Test Error\r\n";
const uint8_t txString_wifiInitialised[] = "Wifi Initialised!\r\n";
const uint8_t txString_wifiInitError[] = "Wifi Init Error\r\n";
const uint8_t txString_wifiConnected[] = "Wifi Connected!\r\n";
const uint8_t txString_commStateManual[] = "MANUAL On\r\n";
const uint8_t txString_commStateAuto[] = "AUTO On\r\n";
const uint8_t txString_connectAPCommand[] = "AT+CWJAP=";

// Strings to compare with
const uint8_t rxString_led0Toggle[] = "Toggle LED0\r\n";
const uint8_t rxString_commStateManual[] = "MANUAL\r\n";
const uint8_t rxString_commStateAuto[] = "AUTO\r\n";
const uint8_t rxString_ATCommandTest[] = "Test AT\r\n";
const uint8_t rxString_wifiInit[] = "Init Wifi\r\n";
const uint8_t rxString_wifiConnectAp[] = "Connect AP\r\n";
const uint8_t rxString_OK[] = "OK\r\n";
const uint8_t rxString_error[] = "ERROR\r\n";
const uint8_t rxString_noSuchFunction[] = "no this fun\r\n";
const uint8_t rxString_noChange[] = "no change\r\n";
const uint8_t rxString_fail[] = "FAIL\r\n";

