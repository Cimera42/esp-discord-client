#include "DiscordJsonListener.h"

void DiscordJsonListener::whitespace(char c)
{
    // Serial.println("whitespace");
}

void DiscordJsonListener::startDocument()
{
    // Serial.println("start document");
}

void DiscordJsonListener::key(String key)
{
    // Serial.println("key: " + key);

    if(state == NONE) {
        if(key == "op") {
            state = OP;
        } else if(key == "s") {
            state = S;
        } else if(key == "t") {
            state = T;
        } else if(key == "d") {
            state = D;
        }
    } else if(state == D) {
        if(key == "session_id") {
            state = D_SESSIONID;
        } else if(key == "heartbeat_interval") {
            state = D_HEARTBEATINTERVAL;
        } else if(key == "member") {
            state = D_MEMBER;
        } else if(key == "channel_id") {
            state = D_CHANNELID;
        } else if(key == "mute") {
            state = D_MUTE;
        } else if(key == "self_mute") {
            state = D_SELFMUTE;
        } else if(key == "suppress") {
            state = D_SUPPRESS;
        } else if(key == "voice_states") {
            state = D_VOICESTATES;
        }
    } else if(state == D_MEMBER) {
        if(key == "user") {
            state = D_MEMBER_USER;
        }
    } else if(state == D_MEMBER_USER) {
        if(key == "id") {
            state = D_MEMBER_USER_ID;
        }
    } else if(state == D_VOICESTATES) {
        if(key == "user_id") {
            state = D_VOICESTATES_USERID;
        }
    } else if(state == D_VOICESTATES_FOUNDUSER) {
        if(key == "mute") {
            state = D_VOICESTATES_FOUNDUSER_MUTE;
        } else if(key == "self_mute") {
            state = D_VOICESTATES_FOUNDUSER_SELFMUTE;
        } else if(key == "suppress") {
            state = D_VOICESTATES_FOUNDUSER_SUPPRESS;
        }
    }
}

void DiscordJsonListener::value(String value)
{
    // Serial.println("value: " + value);
    // Serial.println("state: " + String(state));

    switch(state) {
        case OP: {
            opCode = value;
            state = NONE;
            break;
        }
        case T: {
            t = value;
            state = NONE;
            break;
        }
        case S: {
            s = value;
            state = NONE;
            break;
        }

        case D_SESSIONID: {
            sessionId = value;
            state = D;
            break;
        }
        case D_HEARTBEATINTERVAL: {
            heartbeatInterval = value;
            state = D;
            break;
        }
        case D_CHANNELID: {
            channelId = value;
            state = D;
            break;
        }
        case D_MUTE: {
            mute = value;
            state = D;
            break;
        }
        case D_SELFMUTE: {
            selfMute = value;
            state = D;
            break;
        }
        case D_SUPPRESS: {
            suppress = value;
            state = D;
            break;
        }

        case D_MEMBER_USER_ID: {
            voiceUserId = value;
            state = D;
            break;
        }

        case D_VOICESTATES_USERID: {
            if(value == userIdToFind) {
                userIdFound = true;
                state = D_VOICESTATES_FOUNDUSER;
            } else {
                state = D;
            }
            break;
        }
        case D_VOICESTATES_FOUNDUSER_MUTE: {
            mute = value;
            state = D_VOICESTATES_FOUNDUSER;
            break;
        }
        case D_VOICESTATES_FOUNDUSER_SELFMUTE: {
            selfMute = value;
            state = D_VOICESTATES_FOUNDUSER;
            break;
        }
        case D_VOICESTATES_FOUNDUSER_SUPPRESS: {
            suppress = value;
            state = D_VOICESTATES_FOUNDUSER;
            break;
        }
    }
}

void DiscordJsonListener::endArray()
{
    // Serial.println("end array. ");
}

void DiscordJsonListener::endObject()
{
    // Serial.println("end object. ");
}

void DiscordJsonListener::endDocument()
{
    // Serial.println("end document. ");
}

void DiscordJsonListener::startArray()
{
    // Serial.println("start array. ");
}

void DiscordJsonListener::startObject()
{
    // Serial.println("start object. ");
}

void DiscordJsonListener::reset()
{
    state = NONE;

    opCode = "";
    t = "";
    heartbeatInterval = "";
    s = "";
    sessionId = "";
    voiceUserId = "";
    channelId = "";
    mute = "";
    selfMute = "";
    suppress = "";

    userIdFound = false;
}
