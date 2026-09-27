#pragma once

#include <cstdint>
#include <cstddef>

struct TargetAngles
{
    float panAngle;
    float tiltAngle;
    bool isValid;
};

class CommandParser
{
public:
    CommandParser();

    bool processChar(char incomingChar);

    TargetAngles getTargetAngles() const;

    void reset();

private:
    static constexpr size_t BUFFER_SIZE = 32;
    char m_buffer[BUFFER_SIZE];
    size_t m_bufferIndex;

    TargetAngles m_lastangles;

    bool parseBuffer();
};