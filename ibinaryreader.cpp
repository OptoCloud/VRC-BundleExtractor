#include "ibinaryreader.h"

#include "readerhelpers.h"

#include <string>

VRCE::IBinaryReader::IBinaryReader(std::istream &stream)
    : m_stream(stream)
{
}

std::istream &VRCE::IBinaryReader::stream()
{
    return m_stream;
}

char VRCE::IBinaryReader::readChar()
{
    char value;
    m_stream.get(value);
    return value;
}

bool VRCE::IBinaryReader::readBool()
{
    return (bool)readChar();
}

std::int8_t VRCE::IBinaryReader::read8s()
{
    return (std::int8_t)readChar();
}

std::uint8_t VRCE::IBinaryReader::read8u()
{
    return (std::uint8_t)readChar();
}

std::string VRCE::IBinaryReader::readString()
{
    std::string value;
    std::getline(m_stream, value, '\0');
    return value;
}

void VRCE::IBinaryReader::readInto(std::span<std::uint8_t> span)
{
    m_stream.read((char*)span.data(), span.size());
}

void VRCE::IBinaryReader::alignStream()
{
    m_stream.seekg(((std::int64_t)m_stream.tellg() + 3ll) & ~3ll, m_stream.beg);
}
