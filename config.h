#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT | GUILD_VOICE_STATES_INTENT;

// discord.gg certificate fingerprint
const char * certificateFingerprint = "2c 9f 73 11 96 d1 d6 ab 00 4d 2e f1 2c 4e 12 37 96 17 27 93";

static const char* USER_ID = "132691466177871872";
static const uint8_t LED_PIN = 5;

#endif //CONFIG_H
