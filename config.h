#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "privateConfig.h"

// Intent options can be found in GatewayIntents.h
const uint16_t gateway_intents = GUILD_MESSAGES_INTENT | GUILD_MESSAGE_TYPING_INTENT;

// discord.gg root certificate fingerprint: Baltimore CyberTrust Root
const char * certificateFingerprint = "16af57a9f676b0ab126095aa5ebadef22ab31119d644ac95cd4b93dbf3f26aeb";

#endif //CONFIG_H
