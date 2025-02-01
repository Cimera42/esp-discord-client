#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg certificate fingerprint
// <<FINGERPRINT>> are for automated fingeprint updating with GitHub actions
const char * certificateFingerprint = /*FINGERPRINT>>*/"23 aa db 6e c0 27 46 db 7e 80 c3 8d ce 95 6a 23 6c 18 79 fe"/*<<FINGERPRINT*/;

#endif //CONFIG_H
