#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
// <<FINGERPRINT>> are for automated fingeprint updating with GitHub actions
const char * certificateFingerprint = /*FINGERPRINT>>*/"38 01 01 d8 bb 59 00 19 62 ae ec 60 41 d2 45 e7 45 cd ac 14"/*<<FINGERPRINT*/;

#endif //CONFIG_H
