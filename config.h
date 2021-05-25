#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
const char * certificateFingerprint = "2c 9f 73 11 96 d1 d6 ab 00 4d 2e f1 2c 4e 12 37 96 17 27 93";

#endif //CONFIG_H
