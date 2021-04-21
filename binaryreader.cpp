#include "binaryreader.h"

#include "readerhelpers.h"

#include <string>

VRCE::BinaryReader::BinaryReader(std::istream& stream)
    : IBinaryReader(stream)
{
}

std::int16_t VRCE::BinaryReader::read16s()
{
    return ReaderHelpers::read_type<std::int16_t>(m_stream);
}

std::uint16_t VRCE::BinaryReader::read16u()
{
    return ReaderHelpers::read_type<std::uint16_t>(m_stream);
}

std::int32_t VRCE::BinaryReader::read32s()
{
    return ReaderHelpers::read_type<std::int32_t>(m_stream);
}

std::uint32_t VRCE::BinaryReader::read32u()
{
    return ReaderHelpers::read_type<std::uint32_t>(m_stream);
}

std::int64_t VRCE::BinaryReader::read64s()
{
    return ReaderHelpers::read_type<std::int64_t>(m_stream);
}

std::uint64_t VRCE::BinaryReader::read64u()
{
    return ReaderHelpers::read_type<std::uint64_t>(m_stream);
}

float VRCE::BinaryReader::readFloat()
{
    return std::bit_cast<float>(read32s());
}

double VRCE::BinaryReader::readDouble()
{
    return std::bit_cast<double>(read64s());
}

std::vector<std::int16_t> VRCE::BinaryReader::read16sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int16_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int16_t>(m_stream, vec);

    return vec;
}

std::vector<std::uint16_t> VRCE::BinaryReader::read16uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint16_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint16_t>(m_stream, vec);

    return vec;
}

std::vector<std::int32_t> VRCE::BinaryReader::read32sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int32_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int32_t>(m_stream, vec);

    return vec;
}

std::vector<std::uint32_t> VRCE::BinaryReader::read32uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint32_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint32_t>(m_stream, vec);

    return vec;
}

std::vector<std::int64_t> VRCE::BinaryReader::read64sVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::int64_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::int64_t>(m_stream, vec);

    return vec;
}

std::vector<std::uint64_t> VRCE::BinaryReader::read64uVector()
{
    std::int32_t vecSize = read32s();

    std::vector<std::uint64_t> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<std::uint64_t>(m_stream, vec);

    return vec;
}

std::vector<float> VRCE::BinaryReader::readFloatVector()
{
    std::int32_t vecSize = read32s();

    std::vector<float> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<float>(m_stream, vec);

    return vec;
}

std::vector<double> VRCE::BinaryReader::readDoubleVector()
{
    std::int32_t vecSize = read32s();

    std::vector<double> vec;
    vec.resize(vecSize);

    ReaderHelpers::read_array<double>(m_stream, vec);

    return vec;
}
