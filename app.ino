#define DEBUG

#include <Arduino.h>
#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "WebSocketClient.h"
#include <WiFiClientSecure.h>

#define wifi_ssid ""
#define wifi_password ""

String bot_token = "";

void setup_wifi();

WebSocketClient ws(true);

void setup()
{
    Serial.begin(115200);

    setup_wifi();
}

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
const char *host = "discordapp.com";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
void loop()
{
// Generic HTTPS client for sending messages at some point

// WiFiClientSecure httpsClient;                              //Declare an object of class HTTPClient

// Serial.print("HTTPS Connecting");
//   int r=0; //retry counter
//   while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
//       delay(100);
//       Serial.print(".");
//       r++;
//   }
//   if(r==30) {
//     Serial.println("Connection failed");
//   }
//   else {
//     Serial.println("Connected to web");
//   }
//   httpsClient.print(String("GET ") + "https://discordapp.com/api/gateway" + " HTTP/1.1\r\n" +
//                "Host: " + host + "\r\n" +
//                "Authorization: " + bot_token + "\r\n" +
//                "Connection: close\r\n\r\n");
// Serial.println("request sent");

//   while (httpsClient.connected()) {
//     String line = httpsClient.readStringUntil('\n');
//     if (line == "\r") {
//       Serial.println("headers received");
//       break;
//     }
//   }
//   Serial.println("reply was:");
//   Serial.println("==========");
//   String line;
//   while(httpsClient.available()){
//     line = httpsClient.readStringUntil('\n');  //Read Line by Line
//     Serial.println(line); //Print response
//   }
//   Serial.println("==========");
//   Serial.println("closing connection");

//   delay(2000);  //GET Data at every 2 seconds


	if (!ws.isConnected()) {
        Serial.println("connecting");
        // It technically should fetch url from discordapp.com/api/gateway
		ws.connect("gateway.discord.gg", "https://gateway.discord.gg/", 443);
	} else {
		String msg;
		if (ws.getMessage(msg)) {
			Serial.println(msg);

            // TODO Should maintain heartbeat
            if(msg.indexOf("\"op\":10") != -1) {
                ws.send("{\"op\":2,\"d\":{\"token\":\"" + bot_token + "\",\"properties\":{\"$os\":\"linux\",\"$browser\":\"ESP8266\",\"$device\":\"ESP8266\"},\"compress\":false,\"large_threshold\":250}}");
            }
		}
	}
	delay(500);
}
