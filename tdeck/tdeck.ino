/**
 * @file      Keyboard_T_Deck_Master.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-05-30
 *
 */
#include <Arduino.h>
#include <Wire.h>

#define LILYGO_KB_SLAVE_ADDRESS             0x55
#define LILYGO_KB_BRIGHTNESS_CMD            0x01
#define LILYGO_KB_ALT_B_BRIGHTNESS_CMD      0x02

#define BOARD_POWERON       10
#define BOARD_I2C_SDA       18
#define BOARD_I2C_SCL       8

uint8_t keyInfo[4] = {0x00, 0x00, 0x00, 0x00};    // key_value, alt, mic, speaker

/*
* Dynamically modify backlight brightness at runtime
* Brightness Range: 0 ~ 255
* */
void setKeyboardBrightness(uint8_t value)
{
    Wire.beginTransmission(LILYGO_KB_SLAVE_ADDRESS);
    Wire.write(LILYGO_KB_BRIGHTNESS_CMD);
    Wire.write(value);
    Wire.endTransmission();
}

/*
* Set the default backlight brightness level. If the user sets the backlight to 0
* via setKeyboardBrightness, the default brightness is used when pressing ALT+B,
* rather than the backlight brightness level set by the user. This ensures that
* pressing ALT+B can respond to the backlight being turned on and off normally.
* Brightness Range: 30 ~ 255
* */
void setKeyboardDefaultBrightness(uint8_t value)
{
    Wire.beginTransmission(LILYGO_KB_SLAVE_ADDRESS);
    Wire.write(LILYGO_KB_ALT_B_BRIGHTNESS_CMD);
    Wire.write(value);
    Wire.endTransmission();
}

void setup()
{
    Serial.begin(115200);

    Serial.println("T-Deck Keyboard Master");

    //!⚠️ The board peripheral power control pin needs to be set to HIGH when using the peripheral
    pinMode(BOARD_POWERON, OUTPUT);
    digitalWrite(BOARD_POWERON, HIGH);

    // There needs to be a delay after power on, give LILYGO-KEYBOARD some startup time
    delay(500);

    Wire.begin(BOARD_I2C_SDA, BOARD_I2C_SCL);

    // Check keyboard
    Wire.requestFrom(LILYGO_KB_SLAVE_ADDRESS, 1);
    if (Wire.read() == -1) {
        while (1) {
            Serial.println("LILYGO Keyboard not online .");
            delay(1000);
        }
    }
    // Set the default backlight brightness level.
    setKeyboardDefaultBrightness(127);

}

bool test_bl_done = false;
void loop()
{
    // Read key value from esp32c3
    Wire.requestFrom(LILYGO_KB_SLAVE_ADDRESS, 4);
    for (int i = 0; i < 4 && Wire.available() > 0; i++) {
        // // TODO: Refactor to use an array to store the keyInfo values
        keyInfo[i] = Wire.read();
        // // TODO: Refactor to print each value from keyInfo array
        // TODO: Move out of the loop
        if (keyInfo[i] != (char)0x00) {
            Serial.print("keyValue [");
            Serial.print(i);
            Serial.print("]: ");
            Serial.println(keyInfo[i]);
        }
        // TODO: Add check for when keyInfo[1] is 0x01 or 0x02 or 0x03 and bools are true ?
    }

    // Test brightness
    static uint32_t interval = 0;
    static uint8_t brightness = 0;
    if (millis() > interval && !test_bl_done) {
        // Dynamically modify backlight brightness at runtime
        setKeyboardBrightness(brightness);
        brightness++;
        brightness %= 255;
        if (brightness == 0) {
            Serial.println("Test brightness done..., Press ALT+B test default brightness level");
            setKeyboardBrightness(brightness);
            test_bl_done = true;
        }
        interval = millis() + 50;
    }
    delay(5);
}



