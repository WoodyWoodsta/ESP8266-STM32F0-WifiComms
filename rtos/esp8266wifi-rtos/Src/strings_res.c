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
const uint8_t txString_OKReceived[] = "OK Received!\r\n";
const uint8_t txString_commStateManual[] = "MANUAL On\r\n";
const uint8_t txString_commStateAuto[] = "AUTO On\r\n";

// Strings to compare with
const uint8_t rxString_led0Toggle[] = "Toggle LED0\r\n";
const uint8_t rxString_commStateManual[] = "MANUAL\r\n";
const uint8_t rxString_commStateAuto[] = "AUTO\r\n";
const uint8_t rxString_ATCommandTest[] = "Test AT\r\n";
const uint8_t rxString_OK[] = "OK\r\n";

