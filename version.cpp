#include "version.h"

VRCE::Version VRCE::Version::Parse(const std::string &versionString)
{
    if (versionString.empty())
    {
        throw "Invalid version number" + versionString;
    }

    int major = 0;
    int minor = 0;
    int build = 0;
    VersionType versionType = VersionType::Final;
    int typeNumber = 0;

    std::size_t idx = 0;
    while (true) {
        if (idx >= versionString.size()) {
            throw "Invalid version format";
        }

        char c = versionString[idx++];
        if (c == '.') {
            break;
        }

        major = major * 10 + (int)(c - '0');
    }

    while (true) {
        if (idx >= versionString.size()) {
            break;
        }

        char c = versionString[idx++];
        if (c == '.') {
            break;
        }

        minor = minor * 10 + (int)(c - '0');
    }

    while (true) {
        if (idx >= versionString.size()) {
            break;
        }

        char c = versionString[idx++];
        if (c >= '0' && c <= '9') {
            build = build * 10 + (int)(c - '0');
        }
        else
        {
            switch (c)
            {
                case 'a':
                    versionType = VersionType::Alpha;
                    break;
                case 'b':
                    versionType = VersionType::Beta;
                    break;
                case 'p':
                    versionType = VersionType::Patch;
                    break;
                case 'f':
                    versionType = VersionType::Final;
                    break;
                default:
                {
                    std::string err;
                    err.resize(40);
                    snprintf(err.data(), err.size(), "Unsupported version type %c for version ", c);
                    throw err + versionString;
                }
            }
            break;
        }
    }

    while (true) {
        if (idx >= versionString.size()) {
            break;
        }

        char c = versionString[idx++];
        typeNumber = typeNumber * 10 + (int)(c - '0');
    }

    return Version(major, minor, build, versionType, typeNumber);
}

VRCE::Version::Version()
    : m_data(0)
{
}

VRCE::Version::Version(std::uint16_t major)
    : m_data((std::uint64_t)major << 48)
{
}

VRCE::Version::Version(std::uint16_t major, std::uint8_t minor)
    : m_data(((std::uint64_t)major << 48) | ((std::uint64_t)minor << 40))
{

}

VRCE::Version::Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build)
    : m_data(((std::uint64_t)major << 48) | ((std::uint64_t)minor << 40) | ((std::uint64_t)build << 32))
{

}

VRCE::Version::Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build, VersionType type)
    : m_data(((std::uint64_t)major << 48) | ((std::uint64_t)minor << 40) | ((std::uint64_t)build << 32) | ((std::uint64_t)type << 24))
{

}

VRCE::Version::Version(std::uint16_t major, std::uint8_t minor, std::uint8_t build, VersionType type, std::uint8_t typeNumber)
    : m_data(((std::uint64_t)major << 48) | ((std::uint64_t)minor << 40) | ((std::uint64_t)build << 32) | ((std::uint64_t)type << 24) | ((std::uint64_t)typeNumber << 16))
{

}

VRCE::Version::Version(const VRCE::Version& other)
    : m_data(other.m_data)
{
}

std::uint16_t VRCE::Version::major() const noexcept
{
    return (m_data >> 48) & 0xFFFFull;
}

std::uint8_t VRCE::Version::minor() const noexcept
{
    return (m_data >> 40) & 0xFFull;
}

std::uint8_t VRCE::Version::build() const noexcept
{
    return (m_data >> 32) & 0xFFull;
}

VRCE::VersionType VRCE::Version::type() const noexcept
{
    return (VersionType)((m_data >> 24) & 0xFFull);
}

std::uint8_t VRCE::Version::typeNumber() const noexcept
{
    return (m_data >> 16) & 0xFFull;
}

std::string VRCE::Version::toString() const
{
    return "";
}

VRCE::Version& VRCE::Version::operator=(const VRCE::Version& other)
{
    m_data = other.m_data;

    return *this;
}
