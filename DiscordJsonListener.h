#pragma once

#include "JsonListener.h"

typedef enum {
    NONE,

    OP,
    T,
    S,

    D,
    D_SESSIONID,
    D_HEARTBEATINTERVAL,
    D_CHANNELID,
    D_MUTE,
    D_SELFMUTE,
    D_SUPPRESS,

    D_MEMBER,
    D_MEMBER_USER,
    D_MEMBER_USER_ID,

    D_VOICESTATES,
    D_VOICESTATES_USERID,
    D_VOICESTATES_FOUNDUSER,
    D_VOICESTATES_FOUNDUSER_MUTE,
    D_VOICESTATES_FOUNDUSER_SELFMUTE,
    D_VOICESTATES_FOUNDUSER_SUPPRESS,
} State;

class DiscordJsonListener : public JsonListener
{
private:
    State state;

public:
    virtual void whitespace(char c);

    virtual void startDocument();

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    virtual void endObject();

    virtual void endDocument();

    virtual void startArray();

    virtual void startObject();

    void reset();

    String opCode;
    String t;
    String heartbeatInterval;

    String s;
    String sessionId;

    String voiceUserId;
    String channelId;
    String mute;
    String selfMute;
    String suppress;

    String userIdToFind;
};
