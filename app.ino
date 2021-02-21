#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "WebSocketClient.h"

#include "JsonStreamingParser.h"
#include "DiscordJsonListener.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG Serial.println
#else
#define DEBUG_MSG(MSG)
#endif

#define wifi_ssid ""
#define wifi_password ""

String bot_token = "";

void setup_wifi();

WebSocketClient ws(true);
JsonStreamingParser parser;
DiscordJsonListener listener;

const char *host = "discord.com";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

unsigned long heartbeatInterval = 0;
unsigned long lastHeartbeatAck = 0;
unsigned long lastHeartbeatSend = 0;

bool hasWsSession = false;
String websocketSessionId;
bool hasReceivedWSSequence = false;
unsigned long lastWebsocketSequence = 0;

static const char *USER_ID = "132691466177871872";
static const uint8_t ACTIVE_LED_PIN = 4;
static const uint8_t MUTE_LED_PIN = 5;

void setup()
{
    Serial.begin(115200);

    pinMode(ACTIVE_LED_PIN, OUTPUT);
    digitalWrite(ACTIVE_LED_PIN, LOW);

    pinMode(MUTE_LED_PIN, OUTPUT);
    digitalWrite(MUTE_LED_PIN, LOW);

    setup_wifi();

    parser.setListener(&listener);
    listener.userIdToFind = USER_ID;
}

void setup_wifi()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // Generic HTTPS client for sending messages at some point

    // WiFiClientSecure httpsClient;

    // Serial.print("HTTPS Connecting");
    // int r=0; //retry counter
    // while((!httpsClient.connect(host, httpsPort)) && (r < 30))
    // {
    //     delay(100);
    //     Serial.print(".");
    //     r++;
    // }
    // if(r==30)
    // {
    //     Serial.println("Connection failed");
    // }
    // else
    // {
    //     Serial.println("Connected to web");
    // }
    // httpsClient.print(String("GET ") + "https://discord.com/api/gateway" + " HTTP/1.1\r\n" +
    //             "Host: " + host + "\r\n" +
    //             "Authorization: " + bot_token + "\r\n" +
    //             "Connection: close\r\n\r\n");
    // Serial.println("request sent");

    // while (httpsClient.connected())
    // {
    //     String line = httpsClient.readStringUntil('\n');
    //     if (line == "\r")
    //     {
    //         Serial.println("headers received");
    //         break;
    //     }
    // }
    // Serial.println("reply was:");
    // Serial.println("==========");
    // String line;
    // while(httpsClient.available())
    // {
    //     line = httpsClient.readStringUntil('\n');  //Read Line by Line
    //     Serial.println(line); //Print response
    // }
    // Serial.println("==========");
    // Serial.println("closing connection");

    // delay(2000);  //GET Data at every 2 seconds

    if (!ws.isConnected())
    {
        Serial.println("connecting");
        // It technically should fetch url from discord.com/api/gateway
        ws.connect("gateway.discord.gg", "https://gateway.discord.gg/?v=6&encoding=json", 443);
    }
    else
    {
        unsigned long now = millis();
        if (heartbeatInterval > 0)
        {
            if (now > lastHeartbeatSend + heartbeatInterval)
            {
                if (hasReceivedWSSequence)
                {
                    DEBUG_MSG("Send:: {\"op\":1,\"d\":" + String(lastWebsocketSequence, 10) + "}");
                    ws.send("{\"op\":1,\"d\":" + String(lastWebsocketSequence, 10) + "}");
                }
                else
                {
                    DEBUG_MSG("Send:: {\"op\":1,\"d\":null}");
                    ws.send("{\"op\":1,\"d\":null}");
                }
                lastHeartbeatSend = now;
            }
            if (lastHeartbeatAck > lastHeartbeatSend + (heartbeatInterval / 2))
            {
                DEBUG_MSG("Heartbeat ack timeout");
                ws.disconnect();
                heartbeatInterval = 0;
            }
        }

        String msg;
        if (ws.getMessage(msg))
        {
            DEBUG_MSG(msg);
            listener.reset();
            for (auto c : msg)
            {
                parser.parse(c);
            }
            parser.reset();

            if (listener.opCode == "0")
            {
                if (listener.s != "")
                {
                    lastWebsocketSequence = listener.s.toInt();
                    hasReceivedWSSequence = true;
                }

                if (listener.t == "READY")
                {
                    websocketSessionId = listener.sessionId;
                    hasWsSession = true;
                }
                else if (listener.t == "GUILD_CREATE")
                {
                    if (listener.userIdFound)
                    {
                        digitalWrite(ACTIVE_LED_PIN, HIGH);
                    }
                    if (listener.mute == "true" || listener.selfMute == "true" || listener.suppress == "true")
                    {
                        digitalWrite(MUTE_LED_PIN, HIGH);
                    }
                    // Don't need to go LOW if not muted, as another server/guild may have muted already
                }
                else if (listener.t == "VOICE_STATE_UPDATE")
                {
                    if (listener.voiceUserId == USER_ID)
                    {
                        if (listener.channelId != "null")
                        {
                            digitalWrite(ACTIVE_LED_PIN, HIGH);
                            if (listener.mute == "true" || listener.selfMute == "true" || listener.suppress == "true")
                            {
                                digitalWrite(MUTE_LED_PIN, HIGH);
                            }
                            else
                            {
                                digitalWrite(MUTE_LED_PIN, LOW);
                            }
                        }
                        else
                        {
                            digitalWrite(ACTIVE_LED_PIN, LOW);
                            digitalWrite(MUTE_LED_PIN, LOW);
                        }
                    }
                }
            }
            else if (listener.opCode == "9") // Connection invalid
            {
                ws.disconnect();
                hasWsSession = false;
                heartbeatInterval = 0;
            }
            else if (listener.opCode == "11") // Heartbeat ACKs
            {
                lastHeartbeatAck = now;
            }
            else if (listener.opCode == "10")
            {
                heartbeatInterval = listener.heartbeatInterval.toInt();

                if (hasWsSession)
                {
                    DEBUG_MSG("Send:: {\"op\":6,\"d\":{\"token\":\"" + bot_token + "\",\"session_id\":\"" + websocketSessionId + "\",\"seq\":\"" + String(lastWebsocketSequence, 10) + "\"}}");
                    ws.send("{\"op\":6,\"d\":{\"token\":\"" + bot_token + "\",\"session_id\":\"" + websocketSessionId + "\",\"seq\":\"" + String(lastWebsocketSequence, 10) + "\"}}");
                }
                else
                {
                    DEBUG_MSG("Send:: {\"op\":2,\"d\":{\"token\":\"" + bot_token + "\",\"properties\":{\"$os\":\"linux\",\"$browser\":\"ESP8266\",\"$device\":\"ESP8266\"},\"compress\":false,\"large_threshold\":250}}");
                    ws.send("{\"op\":2,\"d\":{\"token\":\"" + bot_token + "\",\"properties\":{\"$os\":\"linux\",\"$browser\":\"ESP8266\",\"$device\":\"ESP8266\"},\"compress\":false,\"large_threshold\":250}}");
                }

                lastHeartbeatSend = now;
                lastHeartbeatAck = now;
            }
        }
    }
}
