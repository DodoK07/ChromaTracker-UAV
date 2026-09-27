#pragma once

#include <cstdint>

class StepperMotor
{
public:
    enum class Direction
    {
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };

    StepperMotor(uint8_t stepPin, uint8_t dirPin, float stepsPerRev = 200.0f, uint8_t microsteps = 16);

    void init();
    void setSpeed(float rpm);
    void moveSteps(int32_t steps);
    void moveToAngle(float targetAngle);

    bool update();

private:
    uint8_t m_stepPin;
    uint8_t m_dirPin;
    float m_stepsPerRev;
    uint8_t m_microsteps;

    float m_currentAngle;
    int32_t m_targetStep;
    int32_t m_currentStep;

    uint32_t m_stepIntervalUs;
    uint32_t m_lastStepTimeUs;

    void setDirection(Direction dir);
    int32_t angleToSteps(float angle) const;
};
