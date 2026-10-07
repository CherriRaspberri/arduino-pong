#include <Arduino.h>
#include <Bounce2.h>
#include <MicroOscSlip.h>
#include <Chrono.h>

// Btn, chrono and microslip instancing
Bounce2::Button but0;
MicroOscSlip<128> monOsc(&Serial);
Chrono chronoPot;

void setup()
{
    // OSC setup
    Serial.begin(115200);

    // Btn setup
    but0.attach(2, INPUT_PULLUP);
    but0.setPressedState(LOW);

    // Btn LED setup
    pinMode(3, OUTPUT);
}

void loop()
{
    // BUTTON LOGIC -----------------
    //  Update the button state
    but0.update();

    // if the button is pressed, send an OSC message with the address "/but0" and an integer value of 1
    if (but0.pressed())
    {
        monOsc.sendInt("/but0", 1);
    }

    // if the button is released, send an OSC message with the address "/but0" and an integer value of 0
    if (but0.released())
    {
        monOsc.sendInt("/but0", 0);
    }

    // if the button is pressed, turn on the LED on pin 3, otherwise turn it off
    if (but0.isPressed())
    {
        digitalWrite(3, HIGH);
    }
    else
    {
        digitalWrite(3, LOW);
    }

    //------------------------------

    // SLIDER LOGIC -----------------
    // Read the analog value from pin 2 and send it as an OSC message
    if (chronoPot.hasPassed(20))
    {
        chronoPot.restart();
        int value = analogRead(2);
        monOsc.sendInt("/pot", value);
    }
}