/**
* @file      tdeck.ino
* @author    hreikin (hreikin@gmail.com)
* @license   MIT
* @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
* @date      2025-03-07
*/
#include <Arduino.h>
#include <Wire.h>

#define LILYGO_KB_SLAVE_ADDRESS 0x55
#define LILYGO_KB_BRIGHTNESS_CMD 0x01
#define LILYGO_KB_ALT_B_BRIGHTNESS_CMD 0x02

#define BOARD_POWERON 10
#define BOARD_I2C_SDA 18
#define BOARD_I2C_SCL 8

uint8_t keyInfo[5] = {0x00, 0x00, 0x00, 0x00, 0x00}; // key_value, alt, ctrl, mic, speaker

void setup()
{
    Serial.begin(115200);

    Serial.println("T-Deck Keyboard Master");

    // !!!!: The board peripheral power control pin needs to be set to HIGH when using the peripheral
    pinMode(BOARD_POWERON, OUTPUT);
    digitalWrite(BOARD_POWERON, HIGH);

    // There needs to be a delay after power on, give LILYGO-KEYBOARD some startup time
    delay(500);

    Wire.begin(BOARD_I2C_SDA, BOARD_I2C_SCL);

    // Check keyboard
    Wire.requestFrom(LILYGO_KB_SLAVE_ADDRESS, 1);
    if (Wire.read() == -1)
    {
        while (1)
        {
            Serial.println("LILYGO Keyboard not online .");
            delay(1000);
        }
    }
}

void loop()
{
    // Read key value from esp32c3
    Wire.requestFrom(LILYGO_KB_SLAVE_ADDRESS, 5);
    for (int i = 0; i < 5 && Wire.available() > 0; i++)
    {
        keyInfo[i] = Wire.read();
    }
    if (keyInfo[0] != 0x00 || keyInfo[1] != 0x00 || keyInfo[2] != 0x00 || keyInfo[3] != 0x00 || keyInfo[4] != 0x00)
    {
        Serial.print("char: ");
        Serial.println(keyInfo[0]);
        Serial.print("alt: ");
        Serial.println(keyInfo[1]);
        Serial.print("ctrl: ");
        Serial.println(keyInfo[2]);
        Serial.print("mic: ");
        Serial.println(keyInfo[3]);
        Serial.print("speaker: ");
        Serial.println(keyInfo[4]);
    }
    delay(5);
}
