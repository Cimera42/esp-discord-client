#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
// <<FINGERPRINT>> are for automated fingeprint updating with GitHub actions
const char * certificateFingerprint = /*FINGERPRINT>>*/"5a 50 4f 99 b6 3d 95 da 02 e2 21 c7 ae ca d7 1e 32 6d 2c 1c"/*<<FINGERPRINT*/;

#endif //CONFIG_H
