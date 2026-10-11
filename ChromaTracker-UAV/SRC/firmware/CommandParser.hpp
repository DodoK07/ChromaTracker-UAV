<<<<<<< HEAD:SRC/firmware/CommandParser.hpp
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
=======
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
>>>>>>> 154958a933a51eedffe70a7aa25cfb87e1726161:ChromaTracker-UAV/SRC/firmware/CommandParser.hpp
};