#include "endianreader.h"

#include "endianswap.h"
#include "readerhelpers.h"

#include <concepts>
#include <bit>
#include <array>
#include <algorithm>

#if defined(_WIN32) || defined(__WINDOWS__) || defined(__WIN32__)
#include <WinSock2.h>
#elif __linux__
#include <arpa/inet.h>
#endif

VRCE::EndianType g_computerEndianess;

inline VRCE::EndianType VRCE::EndianReader::ComputerEndianess() noexcept
{
    if (0x00FFu == ntohl(0x00FFu)) {
        g_computerEndianess = EndianType::BigEndian;
    }
    else {
        g_computerEndianess = EndianType::LittleEndian;
    }

    return g_computerEndianess;
}

template <typename  T>
inline T read_endian_helper(std::istream& stream, bool diffEndian)
{
    return VRCE::endian_swap_if(VRCE::ReaderHelpers::read_type<T>(stream), diffEndian);
}

VRCE::EndianReader::EndianReader(std::istream& stream, VRCE::EndianType endianess)
    : IBinaryReader(stream)
    , m_differentEndianess(endianess != ComputerEndianess())
{
}

std::int16_t VRCE::EndianReader::read16s()
{
    return read_endian_helper<std::int16_t>(m_stream, m_differentEndianess);
}

std::uint16_t VRCE::EndianReader::read16u()
{
    return read_endian_helper<std::uint16_t>(m_stream, m_differentEndianess);
}

std::int32_t VRCE::EndianReader::read32s()
{
    return read_endian_helper<std::int32_t>(m_stream, m_differentEndianess);
}

std::uint32_t VRCE::EndianReader::read32u()
{
    return read_endian_helper<std::uint32_t>(m_stream, m_differentEndianess);
}

std::int64_t VRCE::EndianReader::read64s()
{
    return read_endian_helper<std::int64_t>(m_stream, m_differentEndianess);
}

std::uint64_t VRCE::EndianReader::read64u()
{
    return read_endian_helper<std::uint64_t>(m_stream, m_differentEndianess);
}

float VRCE::EndianReader::readFloat()
{
    return read_endian_helper<float>(m_stream, m_differentEndianess);
}

double VRCE::EndianReader::readDouble()
{
    return read_endian_helper<double>(m_stream, m_differentEndianess);
}

template <typename  T>
inline std::vector<T> vec_read_endian_helper(std::istream& stream, bool diffEndian)
{
    std::int32_t vecSize = read_endian_helper<std::int32_t>(stream, diffEndian);

    std::vector<T> vec;
    vec.resize(vecSize);

    VRCE::ReaderHelpers::read_array<T>(stream, vec);

    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        *it = VRCE::endian_swap_if(*it, diffEndian);
    }

    return vec;
}

std::vector<std::int8_t> VRCE::EndianReader::read8sVector()
{
    return vec_read_endian_helper<std::int8_t>(m_stream, m_differentEndianess);
}

std::vector<std::uint8_t> VRCE::EndianReader::read8uVector()
{
    return vec_read_endian_helper<std::uint8_t>(m_stream, m_differentEndianess);
}

std::vector<std::int16_t> VRCE::EndianReader::read16sVector()
{
    return vec_read_endian_helper<std::int16_t>(m_stream, m_differentEndianess);
}

std::vector<std::uint16_t> VRCE::EndianReader::read16uVector()
{
    return vec_read_endian_helper<std::uint16_t>(m_stream, m_differentEndianess);
}

std::vector<std::int32_t> VRCE::EndianReader::read32sVector()
{
    return vec_read_endian_helper<std::int32_t>(m_stream, m_differentEndianess);
}

std::vector<std::uint32_t> VRCE::EndianReader::read32uVector()
{
    return vec_read_endian_helper<std::uint32_t>(m_stream, m_differentEndianess);
}

std::vector<std::int64_t> VRCE::EndianReader::read64sVector()
{
    return vec_read_endian_helper<std::int64_t>(m_stream, m_differentEndianess);
}

std::vector<std::uint64_t> VRCE::EndianReader::read64uVector()
{
    return vec_read_endian_helper<std::uint64_t>(m_stream, m_differentEndianess);
}

std::vector<float> VRCE::EndianReader::readFloatVector()
{
    return vec_read_endian_helper<float>(m_stream, m_differentEndianess);
}

std::vector<double> VRCE::EndianReader::readDoubleVector()
{
    return vec_read_endian_helper<double>(m_stream, m_differentEndianess);
}
