#include "memoryreadsource.h"

#include <cstring>

VRCE::IReadSource::Type VRCE::MemoryReadSource::InterfaceType() const { return IReadSource::Type::Memory; }

VRCE::MemoryReadSource::MemoryReadSource(std::shared_ptr<const std::vector<std::uint8_t>> data)
    : VRCE::IReadSource()
    , m_data(data)
    , m_pos(0)
{
}

std::uint8_t VRCE::MemoryReadSource::get()
{
    return m_data->at(m_pos++);
}

void VRCE::MemoryReadSource::read(std::uint8_t* buf, std::size_t size)
{
    std::memcpy(buf, m_data->data() + m_pos, size);
    m_pos += size;
}

std::string VRCE::MemoryReadSource::readString()
{
    const std::uint8_t* beg = m_data->data() + m_pos;
    const std::uint8_t* it = beg;

    while (*it != 0) { it++; }

    m_pos += (it - beg) + 1;

    return std::string(beg, it);
}

void VRCE::MemoryReadSource::seekBeg(std::ptrdiff_t offset)
{
    m_pos = offset;
}

void VRCE::MemoryReadSource::seekRel(std::ptrdiff_t offset)
{
    m_pos += offset;
}

std::ptrdiff_t VRCE::MemoryReadSource::position() const
{
    return m_pos;
}
