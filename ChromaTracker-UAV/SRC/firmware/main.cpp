#include "StepperMotor.hpp"
#include "CommandParser.hpp"

// Donanıma özel / platform bağımlı fonksiyon prototipleri
// (Gerçek donanımda Arduino/ESP32 için Serial.read(), micros() ve digitalWrite() gibi fonksiyonlar bağlanacak)
extern bool readSerialChar(char &c);
extern uint32_t getCurrentMicros();
extern void setPinState(uint8_t pin, bool state);

// Motor Pin Tanımlamaları (Donanıma göre güncellenebilir)
constexpr uint8_t PAN_STEP_PIN = 2;
constexpr uint8_t PAN_DIR_PIN = 3;
constexpr uint8_t TILT_STEP_PIN = 4;
constexpr uint8_t TILT_DIR_PIN = 5;

StepperMotor panMotor(PAN_STEP_PIN, PAN_DIR_PIN, 200.0f, 16);
StepperMotor tiltMotor(TILT_STEP_PIN, TILT_DIR_PIN, 200.0f, 16);

CommandParser commandParser;

void setup()
{

    panMotor.setSpeed(60.0f);
    tiltMotor.setSpeed(60.0f);

    panMotor.init();
    tiltMotor.init();
}

void loop()
{

    char incomingChar;
    while (readSerialChar(incomingChar))
    {
        if (commandParser.processChar(incomingChar))
        {

            TargetAngles angles = commandParser.getTargetAngles();
            if (angles.isValid)
            {
                panMotor.moveToAngle(angles.panAngle);
                tiltMotor.moveToAngle(angles.tiltAngle);
            }
        }
    }

    panMotor.update();
    tiltMotor.update();
}

int main()
{
    setup();

    while (true)
    {
        loop();
    }

    return 0;
}