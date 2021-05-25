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

2. Copy `privateConfig.template.h` and rename to `privateConfig.h`.

3. Set configuration in `config.h` and `privateConfig.h`.

    |Name|Value|Location|
    |-|-|-|
    |`wifi_ssid`|SSID of the wifi to connect to|`privateConfig.h`|
    |`wifi_password`|Password for the wifi to connect to|`privateConfig.h`|
    |`bot_token`|Token to authenticate websocket connection<br/>Discord bots can be created and tokens generated at the [Developer Documentation](https://discord.com/developers/applications).|`privateConfig.h`|
    |`gateway_intents`|Data to be sent over websocket connection<br/>Options can be found in [`GatewayIntents.h`](./GatewayIntents.h)<br/>  - Bitwise OR (`\|`) for multiple.<br/>More info can be found at: https://discord.com/developers/docs/topics/gateway#gateway-intents|`config.h`|

4. Build and upload to ESP board

- If there are any problems, feel free to create an [issue on GitHub](https://github.com/Cimera42/esp-discord-client/issues)

## Potential Issues

Here's some common problems which may be preventing the client from working properly.

### Large servers

Due to the limited memory of the ESP8266, some websocket messages may be too large and crash the program. For this reason, it is not recommended to use the `GUILDS_INTENT` intent, as it includes a message of the full state of the bot's guilds when connecting the websocket client.

### Incorrect SSL fingerprint

If the WebSocket gets into a loop connecting, you may need to update the SSL certificate fingerprint.

1. Enable debugging of SSL through the `DEBUG_ESP_SSL` and `DEBUG_ESP_PORT=Serial` defines.

    (These will have to be set in such a way that they affect the library, e.g. `arduino.json / buildPreferences / build.extra_flags` for VSCode, `preferences.txt` for Arduino IDE).

2. Ensure the `certificateFingerprint` in `config.h` is set to a valid fingerprint format (20 pairs of hexadecimal characters).

    This makes sure the library should print out the correct token we want.

3. Run the application and connect to the serial log

4. Copy the `received` fingerprint from the serial log into `certificateFingerprint` in `config.h`.

    Example output:
    ```
    BSSL:insecure_end_chain: Received cert FP doesn't match
    BSSL:insecure_end_chain: expected 65 35 f4 58 de 33 46 2d 16 1e 4b 35 c1 f1 97 8f 95 b2 3a 18
    BSSL:insecure_end_chain: received 2c 9f 73 11 96 d1 d6 ab 00 4d 2e f1 2c 4e 12 37 96 17 27 93
    ```

## Used Libraries:
### [esp8266-websocketclient](https://github.com/hellerchr/esp8266-websocketclient)
Some custom modifications:
- Accept lowercase http headers
- Non-blocking `getMessage`
- Allow setting WiFiClientSecure SSL Fingerprint
- Log message when client connection fails

### [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
Used to decode JSON payloads from Discord.

### [ESP8266 Arduino core - v2.7.4](https://github.com/esp8266/Arduino/releases/tag/2.7.4)
Arduino core for ESP8266 WiFi chip

## Other Resources

Based on https://github.com/Cimera42/DiscordBot
