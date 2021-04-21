#include "hash128.h"

#include "endianreader.h"

int VRCE::Classes::Misc::Hash128::ToSerializedVersion(VRCE::Version version)
{
    if (version >= Version(5))
    {
        return 2;
    }

    return 1;
}

VRCE::Classes::Misc::Hash128::Hash128()
    : m_data0(0)
    , m_data1(0)
    , m_data2(0)
    , m_data3(0)
{

}

VRCE::Classes::Misc::Hash128::Hash128(std::uint32_t v)
    : m_data0(v)
    , m_data1(0)
    , m_data2(0)
    , m_data3(0)
{
}

VRCE::Classes::Misc::Hash128::Hash128(std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3)
    : m_data0(v0)
    , m_data1(v1)
    , m_data2(v2)
    , m_data3(v3)
{
}

void VRCE::Classes::Misc::Hash128::read(VRCE::IBinaryReader& reader)
{
    m_data0 = reader.read32u();
    m_data1 = reader.read32u();
    m_data2 = reader.read32u();
    m_data3 = reader.read32u();
}

std::uint32_t VRCE::Classes::Misc::Hash128::data0() const
{
    return m_data0;
}

std::uint32_t VRCE::Classes::Misc::Hash128::data1() const
{
    return m_data1;
}

std::uint32_t VRCE::Classes::Misc::Hash128::data2() const
{
    return m_data2;
}

std::uint32_t VRCE::Classes::Misc::Hash128::data3() const
{
    return m_data3;
}
