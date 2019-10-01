# ESP Discord WebSocket Client

Implements a basic Discord WebSocket client as documented at https://discordapp.com/developers/docs/topics/gateway.

|Features|Status|
|-|-|
|Discord WebSocket gateway connect and receive|Working|
|WS Heartbeat|Working|
|JSON Parsing|Working|
|API Requests|To-do|
|Get Gateway URL from API|To-do|

## Installation

1. Install ESP board for Arduino as outlined on the [official documentation](https://arduino-esp8266.readthedocs.io/en/latest/installing.html)

1. Build and upload to ESP board

- If there are any problems, feel free to create an [issue on GitHub](https://github.com/Cimera42/esp-discord-client/issues)

## Used Libraries:
### [esp8266-websocketclient](https://github.com/hellerchr/esp8266-websocketclient)
Some custom modifications:
- Accept lowercase http headers
- Non-blocking `getMessage`

### [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
Used to decode JSON payloads from Discord.

## Other Resources

Based on https://github.com/Cimera42/DiscordBot
