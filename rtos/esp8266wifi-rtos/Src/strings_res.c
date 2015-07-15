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
const uint8_t ATCommandTestTxString[] = "AT\r\n";
const uint8_t commStateManualTxString[] = "MANUAL Mode Started\r\n";
const uint8_t commStateAutoTxString[] = "AUTO Mode Started\r\n";

// Strings to compare with
const uint8_t led0ToggleRxString[] = "Toggle LED0";
const uint8_t commStateManualRxString[] = "MANUAL";
const uint8_t commStateAutoRxString[] = "AUTO";
const uint8_t testATRxString[] = "Test AT";

