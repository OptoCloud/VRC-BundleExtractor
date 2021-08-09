#include "binaryreader.h"

#include "filereadsource.h"
#include "memoryreadsource.h"
#include "readerhelpers.h"

#include <string>

VRCE::BinaryReader::BinaryReader(const std::filesystem::path& path)
    : m_readsource(new VRCE::FileReadSource(path))
{
    m_readsource->refCount++;
}

VRCE::BinaryReader::BinaryReader(std::shared_ptr<std::vector<std::uint8_t>> data)
    : m_readsource(new VRCE::MemoryReadSource(data))
{
    m_readsource->refCount++;
}

VRCE::BinaryReader::BinaryReader(const VRCE::BinaryReader& other)
    : m_readsource(other.m_readsource)
{
    m_readsource->refCount++;
}

VRCE::BinaryReader::~BinaryReader()
{
    if (--m_readsource->refCount == 0) {
        delete m_readsource;
    }
}

VRCE::IReadSource* VRCE::BinaryReader::readSource()
{
    return m_readsource;
}

bool VRCE::BinaryReader::isValid() const
{
    return m_readsource != nullptr && m_readsource->isValid();
}

std::ptrdiff_t VRCE::BinaryReader::position() const
{
    return m_readsource->position();
}

void VRCE::BinaryReader::seekBeg(std::ptrdiff_t offset)
{
    m_readsource->seekBeg(offset);
}

void VRCE::BinaryReader::seekRel(std::ptrdiff_t offset)
{
    m_readsource->seekRel(offset);
}

char VRCE::BinaryReader::readChar()
{
    return m_readsource->get();
}

bool VRCE::BinaryReader::readBool()
{
    return (bool)m_readsource->get();
}

std::int8_t VRCE::BinaryReader::read8s()
{
    return (std::int8_t)m_readsource->get();
}

std::uint8_t VRCE::BinaryReader::read8u()
{
    return (std::uint8_t)m_readsource->get();
}

std::int16_t VRCE::BinaryReader::read16s()
{
    return ReaderHelpers::read_type<std::int16_t>(m_readsource);
}

std::uint16_t VRCE::BinaryReader::read16u()
{
    return ReaderHelpers::read_type<std::uint16_t>(m_readsource);
}

std::int32_t VRCE::BinaryReader::read32s()
{
    return ReaderHelpers::read_type<std::int32_t>(m_readsource);
}

std::uint32_t VRCE::BinaryReader::read32u()
{
    return ReaderHelpers::read_type<std::uint32_t>(m_readsource);
}

std::int64_t VRCE::BinaryReader::read64s()
{
    return ReaderHelpers::read_type<std::int64_t>(m_readsource);
}

std::uint64_t VRCE::BinaryReader::read64u()
{
    return ReaderHelpers::read_type<std::uint64_t>(m_readsource);
}

float VRCE::BinaryReader::readFloat()
{
    return std::bit_cast<float>(read32s());
}

double VRCE::BinaryReader::readDouble()
{
    return std::bit_cast<double>(read64s());
}

std::string VRCE::BinaryReader::readString()
{
    return m_readsource->readString();
}

std::vector<int8_t> VRCE::BinaryReader::read8sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int8_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int8_t>(m_readsource, vec);

    return vec;
}

std::vector<uint8_t> VRCE::BinaryReader::read8uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint8_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint8_t>(m_readsource, vec);

    return vec;
}

std::vector<std::int16_t> VRCE::BinaryReader::read16sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int16_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int16_t>(m_readsource, vec);

    return vec;
}

std::vector<std::uint16_t> VRCE::BinaryReader::read16uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint16_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint16_t>(m_readsource, vec);

    return vec;
}

std::vector<std::int32_t> VRCE::BinaryReader::read32sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int32_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int32_t>(m_readsource, vec);

    return vec;
}

std::vector<std::uint32_t> VRCE::BinaryReader::read32uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint32_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint32_t>(m_readsource, vec);

    return vec;
}

std::vector<std::int64_t> VRCE::BinaryReader::read64sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int64_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int64_t>(m_readsource, vec);

    return vec;
}

std::vector<std::uint64_t> VRCE::BinaryReader::read64uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint64_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint64_t>(m_readsource, vec);

    return vec;
}

std::vector<float> VRCE::BinaryReader::readFloatVector()
{
    std::int32_t vecSize = read32s();

    std::vector<float> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<float>(m_readsource, vec);

    return vec;
}

std::vector<double> VRCE::BinaryReader::readDoubleVector()
{
    std::int32_t vecSize = read32s();

    std::vector<double> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<double>(m_readsource, vec);

    return vec;
}

void VRCE::BinaryReader::readInto(std::span<std::uint8_t> span)
{
    m_readsource->read(span.data(), span.size());
}

void VRCE::BinaryReader::alignStream()
{
    m_readsource->seekBeg((m_readsource->position() + 3ll) & ~3ll);
}

VRCE::BinaryReader& VRCE::BinaryReader::operator =(const VRCE::BinaryReader& other)
{
    if (m_readsource != other.m_readsource) {
        if (--m_readsource->refCount == 0) {
            delete m_readsource;
        }

        m_readsource = other.m_readsource;
        m_readsource->refCount++;
    }

    return *this;
}
