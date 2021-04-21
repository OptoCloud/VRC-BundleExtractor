#ifndef VERSION_H
#define VERSION_H

#include "versiontype.h"

#include <string>
#include <cstdint>

namespace VRCE {
struct Version
{
    static Version Parse(const std::string& versionString);

    Version();
    Version(std::uint16_t major);
    Version(std::uint16_t major, std::uint8_t minor);
    Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build);
    Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build, VersionType type);
    Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build, VersionType type, std::uint8_t typeNumber);
    Version(const VRCE::Version& other);

    std::uint16_t major() const noexcept;
    std::uint8_t minor() const noexcept;
    std::uint8_t build() const noexcept;
    VersionType type() const noexcept;
    std::uint8_t typeNumber() const noexcept;

    void setMajor(std::uint16_t major) noexcept
    {
        m_data &= ~((0xFFFFull) << 48);
        m_data |= ((std::uint64_t)major << 48);
    }

    void setMinor(std::uint8_t minor) noexcept
    {
        m_data &= ~((0xFFull) << 40);
        m_data |= ((std::uint64_t)minor << 40);
    }
    void setBuild(std::uint8_t patch) noexcept
    {
        m_data &= ~((0xFFull) << 32);
        m_data |= ((std::uint64_t)patch << 32);
    }
    void setType(VersionType type) noexcept
    {
        m_data &= ~((0xFFull) << 24);
        m_data |= ((std::uint64_t)type << 24);
    }
    void setTypeNumber(std::uint8_t typeNumber) noexcept
    {
        m_data &= ~((0xFFull) << 16);
        m_data |= ((std::uint64_t)typeNumber << 16);
    }

    std::string toString() const;

    bool operator==(const Version& other) const noexcept { return m_data == other.m_data; }
    bool operator!=(const Version& other) const noexcept { return m_data != other.m_data; }
    bool operator< (const Version& other) const noexcept { return m_data <  other.m_data; }
    bool operator> (const Version& other) const noexcept { return m_data >  other.m_data; }
    bool operator<=(const Version& other) const noexcept { return m_data <= other.m_data; }
    bool operator>=(const Version& other) const noexcept { return m_data >= other.m_data; }

    VRCE::Version& operator=(const VRCE::Version& other);
private:
    std::uint64_t m_data;
};
/*
const Version VersionMin { 0x0000000000000000ull };
const Version VersionMax { 0xFFFFFFFFFFFFFFFFull };
*/
}

#endif // VERSION_H
