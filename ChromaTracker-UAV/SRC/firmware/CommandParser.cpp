#include "CommandParser.hpp"
#include <cstdlib>
#include <cstring>

CommandParser::CommandParser()
    : m_bufferIndex(0),
      m_lastAngles{0.0f, 0.0f, false}
{
    reset();
}

void CommandParser::reset()
{
    m_bufferIndex = 0;
    std::memset(m_buffer, 0, BUFFER_SIZE);
}

bool CommandParser::processChar(char incomingChar)
{

    if (incomingChar == '\n' || incomingChar == '\r')
    {
        if (m_bufferIndex > 0)
        {
            m_buffer[m_bufferIndex] = '\0'; // String sonlandırıcı
            bool success = parseBuffer();
            reset();
            return success;
        }
        return false;
    }

    if (m_bufferIndex < BUFFER_SIZE - 1)
    {
        m_buffer[m_bufferIndex++] = incomingChar;
    }
    else
    {
        reset();
    }

    return false;
}

bool CommandParser::parseBuffer()

    char *panPtr = std::strstr(m_buffer, "P:");
char *tiltPtr = std::strstr(m_buffer, "T:");

if (panPtr != nullptr && tiltPtr != nullptr)
{
    float pan = static_cast<float>(std::atof(panPtr + 2));
    float tilt = static_cast<float>(std::atof(tiltPtr + 2));

    m_lastAngles.panAngle = pan;
    m_lastAngles.tiltAngle = tilt;
    m_lastAngles.isValid = true;
    return true;
}

m_lastAngles.isValid = false;
return false;
}

TargetAngles CommandParser::getTargetAngles() const
{
    return m_lastAngles;
}