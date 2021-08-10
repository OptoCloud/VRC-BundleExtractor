#ifndef STORAGEBLOCKFLAGS_H
#define STORAGEBLOCKFLAGS_H

#include "compressiontype.h"

#include <cstdint>

namespace VRCE::BundleFiles {
struct StorageBlockFlags
{
    enum Enums : std::uint16_t
    {
        CompressionTypeMask = 0x3F,

        Streamed            = 0x40,
    };

    constexpr StorageBlockFlags() noexcept : m_value(0) {}
    constexpr StorageBlockFlags(std::uint16_t value) noexcept : m_value(value) {}

    constexpr void setValue(std::uint16_t value) noexcept { m_value = value; }
    constexpr std::uint16_t value() const noexcept { return m_value; }

    constexpr CompressionType compression() const noexcept { return (CompressionType)(m_value & Enums::CompressionTypeMask); }
    constexpr bool isStreamed() const noexcept { return (m_value & Enums::Streamed) != 0; };
private:
    std::uint16_t m_value;
};

}

#endif // STORAGEBLOCKFLAGS_H
