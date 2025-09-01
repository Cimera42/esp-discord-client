#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
// <<FINGERPRINT>> are for automated fingeprint updating with GitHub actions
const char * certificateFingerprint = /*FINGERPRINT>>*/"cf 5f 07 69 1d ab 5c 65 57 c9 a7 fb a7 e9 ab 31 1f d1 65 98"/*<<FINGERPRINT*/;

#endif //CONFIG_H
