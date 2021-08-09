#include "filereadsource.h"

VRCE::IReadSource::Type VRCE::FileReadSource::InterfaceType() const { return IReadSource::Type::File; }

VRCE::FileReadSource::FileReadSource(const std::filesystem::path& path)
    : VRCE::IReadSource()
    , m_stream(std::make_shared<std::ifstream>(path))
{
}

bool VRCE::FileReadSource::isValid() const { return m_stream->is_open(); }

std::uint8_t VRCE::FileReadSource::get()
{
    return (std::uint8_t)m_stream->get();
}

void VRCE::FileReadSource::read(std::uint8_t* buf, std::size_t size)
{
    m_stream->read((char*)buf, size);
}

std::string VRCE::FileReadSource::readString()
{
    std::string value;
    std::getline(*m_stream, value, '\0');
    return value;
}

void VRCE::FileReadSource::seekBeg(std::ptrdiff_t offset)
{
    m_stream->seekg(offset, std::ios::beg);
}

void VRCE::FileReadSource::seekRel(std::ptrdiff_t offset)
{
    m_stream->seekg(offset, std::ios::cur);
}

std::ptrdiff_t VRCE::FileReadSource::position() const
{
    return (std::ptrdiff_t)m_stream->tellg();
}
