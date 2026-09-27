#include "StepperMotor.hpp"
#include <cmath>

extern uint32_t getCurrentMicros();
extern void setPinState(uint8_t pin, bool state);

StepperMotor::StepperMotor(uint8_t stepPin, uint8_t dirPin, float stepsPerRev, uint8_t microsteps)
    : m_stepPin(stepPin),
      m_dirPin(dirPin),
      m_stepsPerRev(stepsPerRev),
      m_microsteps(microsteps),
      m_currentAngle(0.0f),
      m_targetStep(0),
      m_currentStep(0),
      m_stepIntervalUs(1000),
      m_lastStepTimeUs(0) {}

void StepperMotor::init() {
    setSpeed(60.0f); // Normal 60 RPM
}

void StepperMotor::setSpeed(float rpm) {
    if (rpm <= 0.0f) return;
    float stepsPerSec = (m_stepsPerRev * m_microsteps * rpm) / 60.0f;
    m_stepIntervalUs = static_cast<uint32_t>(1000000.0f / stepsPerSec);
}

int32_t StepperMotor::angleToSteps(float angle) const {
    float totalStepsPerRev = m_stepsPerRev * m_microsteps;
    return static_cast<int32_t>((angle / 360.0f) * totalStepsPerRev);
}

void StepperMotor::moveToAngle(float targetAngle) {
    m_targetStep = angleToSteps(targetAngle);
}

void StepperMotor::setDirection(Direction dir) {
    setPinState(m_dirPin, dir == Direction::CLOCKWISE);
}

bool StepperMotor::update() {
    if (m_currentStep == m_targetStep) {
        return false; // Mission completed
    }

    uint32_t now = getCurrentMicros();
    if (now - m_lastStepTimeUs >= m_stepIntervalUs) {
        m_lastStepTimeUs = now;

        if (m_targetStep > m_currentStep) {
            setDirection(Direction::CLOCKWISE);
            m_currentStep++;
        } else {
            setDirection(Direction::COUNTER_CLOCKWISE);
            m_currentStep--;
        }

        // STEP pinine kare dalga sinyali (Pulse)
        setPinState(m_stepPin, true);
        // Kısa bekleme sonrası LOW yapma mantığı donanım katmanına bırakılabilir
        setPinState(m_stepPin, false); 

        return true;
    }

    return false;
}