/**
 * @file      keyboard.ino
 * @brief     Simple program to read key matrix and send key information over I2C.
 * @author    hreikin (hreikin@gmail.com)
 * @license   MIT
 * @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
 * @date      2025-03-07
 */

#define CONFIG_IDF_TARGET_ESP32C3       // This can be removed if using esp.idf and setting a build flag instead

#ifdef CONFIG_IDF_TARGET_ESP32C3
#include <Arduino.h>
#include <Wire.h>
#include "keyboard.hpp"

/**
 * @brief Initializes the keyboard.
 * 
 * Sets up the CPU frequency, serial communication, I2C communication, and keyboard backlight.
 */
void setup()
{
    // Reduce operating power consumption arduino esp32 core version must >= 2.0.17
    /*
    * 10MHZ can also run normally, but for stable operation, change the frequency to 80MHZ to prevent it from failing to run due to crystal oscillator problems
    * setCpuFrequencyMhz(10);
    * */
    setCpuFrequencyMhz(80);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Wire.onRequest(onRequest);
    Wire.begin((uint8_t)I2C_DEV_ADDR, SDA, SCL, 100000UL);
    Serial.println("Starting keyboard work!");
    // TODO: Upstream this change to fix the error reported over serial by the keyboard: E (229) ledc: ledc_get_duty(740): LEDC is not initialized
    ledcSetup(KEYBOARD_BRIGHTNESS_CH, KEYBOARD_BRIGHTNESS_FREQ, KEYBOARD_BRIGHTNESS_RES);
    ledcAttachPin(KEYBOARD_BACKLIGHT_PIN, KEYBOARD_BRIGHTNESS_CH);
    ledcWrite(KEYBOARD_BRIGHTNESS_CH, KEYBOARD_BRIGHTNESS_DEFAULT);
    Serial.println("4");
    for (int x = 0; x < rowCount; x++) {
        Serial.print(rows[x]); Serial.println(" as input");
        pinMode(rows[x], INPUT);
    }
    for (int x = 0; x < colCount; x++) {
        Serial.print(cols[x]); Serial.println(" as input-pullup");
        pinMode(cols[x], INPUT_PULLUP);
    }
    Serial.println("************************************");
}

/**
 * @brief Reads the key matrix and sends key information.
 * 
 * These functions are called repeatedly in the main loop to read the state of the key matrix
 * and send the key information over I2C.
 */
void loop()
{
    readKeyMatrix();
    sendKeyInfo();
}

#else
#include <Arduino.h>
void setup()
{
    Serial.begin(115200);
}
void loop()
{
    Serial.println("SKETCH ONLY FOR LILYGO-KEYBOARD");
    delay(1000);
}
#endif