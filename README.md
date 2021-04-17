# ESP Discord WebSocket Client

Implements a basic Discord WebSocket client as documented at https://discord.com/developers/docs/topics/gateway.

|Features|Status|
|-|-|
|Discord WebSocket gateway connect and receive|Working|
|WS Heartbeat|Working|
|JSON Parsing|Working|
|API Requests|To-do|
|Get Gateway URL from API|To-do|

See the [`mute_led`](https://github.com/Cimera42/esp-discord-client/tree/mute_led) branch for an example application which turns on an LED when the specified user is muted in a voice channel.

## Installation

1. Install ESP board for Arduino as outlined on the [official documentation](https://arduino-esp8266.readthedocs.io/en/latest/installing.html)

2. Set configuration at the top of `app.ino`.

    |Name|Value|
    |-|-|
    |`wifi_ssid`|SSID of the wifi to connect to|
    |`wifi_password`|Password for the wifi to connect to|
    |`bot_token`|Token to authenticate websocket connection<br/>Discord bots can be created and tokens generated at the [Developer Documentation](https://discord.com/developers/applications).|
    |`gateway_intents`|Data to be sent over websocket connection<br/>Options can be found in [`GatewayIntents.h`](./GatewayIntents.h)<br/>  - Bitwise OR (`\|`) for multiple.<br/>More info can be found at: https://discord.com/developers/docs/topics/gateway#gateway-intents|


3. Build and upload to ESP board

- If there are any problems, feel free to create an [issue on GitHub](https://github.com/Cimera42/esp-discord-client/issues)

## Potential Issues

Here's some common problems which may be preventing the client from working properly.

### Large servers

Due to the limited memory of the ESP8266, some websocket messages may be too large and crash the program. For this reason, it is not recommended to use the `GUILDS_INTENT` intent, as it includes a message of the full state of the bot's guilds when connecting the websocket client.

## Used Libraries:
### [esp8266-websocketclient](https://github.com/hellerchr/esp8266-websocketclient)
Some custom modifications:
- Accept lowercase http headers
- Non-blocking `getMessage`

### [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
Used to decode JSON payloads from Discord.

## Other Resources

Based on https://github.com/Cimera42/DiscordBot
