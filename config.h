#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
// <<FINGERPRINT>> are for automated fingeprint updating with GitHub actions
const char * certificateFingerprint = /*FINGERPRINT>>*/"e1 83 99 07 09 25 67 95 e6 ce 86 5e c7 da 97 73 dc 66 a6 72"/*<<FINGERPRINT*/;

#endif //CONFIG_H
