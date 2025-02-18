#define CONFIG_IDF_TARGET_ESP32C3

#ifdef CONFIG_IDF_TARGET_ESP32C3
#include <Arduino.h>
#include <Wire.h>
#include "keyboard.hpp"

void setup()
{
    // Reduce operating power consumption arduino esp32 core version must >= 2.0.17
    /*
    * 10MHZ can also run normally, but for stable operation, change the frequency to 80MHZ to prevent it from failing to run due to crystal oscillator problems
    * setCpuFrequencyMhz(10);
    * */
    setCpuFrequencyMhz(80);

    // put your setup code here, to run once:
    Serial.begin(115200);

    Serial.setDebugOutput(true);
    Wire.onRequest(onRequest);
    Wire.onReceive(onReceive);
    Wire.begin((uint8_t)I2C_DEV_ADDR, SDA, SCL, 100000UL);

    Serial.println("Starting keyboard work!");

    // TODO: Upstream this change to fix the error reported over serial by the keyboard: E (229) ledc: ledc_get_duty(740): LEDC is not initialized
    ledcSetup(KB_BRIGHTNESS_CH, KB_BRIGHTNESS_FREQ, KB_BRIGHTNESS_RES);
    ledcAttachPin(keyboard_BL_PIN, KB_BRIGHTNESS_CH);
    ledcWrite(KB_BRIGHTNESS_CH, KB_BRIGHTNESS_BOOT_DUTY);

    Serial.println("4");
    for (int x = 0; x < rowCount; x++) {
        Serial.print(rows[x]); Serial.println(" as input");
        pinMode(rows[x], INPUT);
    }

    for (int x = 0; x < colCount; x++) {
        Serial.print(cols[x]); Serial.println(" as input-pullup");
        pinMode(cols[x], INPUT_PULLUP);
    }

}

void loop()
{
    readKeyMatrix();
    sendKeyInfo();

    // key 3,3 is the enter key
    if (keyPressed(3, 3)) {
        Serial.println();
        comdata = (char)0x0D;
        comdata_flag = true;
    }
    if (keyPressed(4, 3)) {
        Serial.println("backspace");
        comdata = (char)0x08;
        comdata_flag = true;
    }
    if (keyHeld(0, 4) && keyPressed(3, 4)) { //Alt+B
        Serial.println("Alt+B");
        // If the software sets the duty cycle to 0, then the value set
        // by the ATL+B register is used to ensure that ALT+B can normally light up the backlight.
        if (BL_state) {
            BL_state = false;
            ledcWrite(KB_BRIGHTNESS_CH, 0); //turn off
        } else {
            BL_state = true;
            if (kb_brightness_duty == 0) {
                Serial.println("User set bl duty is zero,use setting duty");
                ledcWrite(KB_BRIGHTNESS_CH, kb_brightness_setting_duty);
            } else {
                Serial.println("Duty is not zero ,use user setting bl value");
                ledcWrite(KB_BRIGHTNESS_CH, kb_brightness_duty);
            }
        }
        comdata_flag = false;   //Don't send char
    }
    if (keyHeld(0, 4) && keyPressed(2, 5)) { //Alt+C
        Serial.println("Alt+C");
        comdata = (char)0x0C;
        comdata_flag = true;
    }
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