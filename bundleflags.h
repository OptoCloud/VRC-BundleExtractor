#ifndef BUNDLEFLAGS_H
#define BUNDLEFLAGS_H

#include "compressiontype.h"

#include <cstdint>

namespace VRCE::BundleFiles {
struct BundleFlags
{
    enum Enums : int
    {
        CompressionTypeMask             = 0x3F,

        BlocksAndDirectoryInfoCombined  = 0x40,
        BlocksInfoAtTheEnd              = 0x80,
        OldWebPluginCompatibility       = 0x100,
    };

    constexpr BundleFlags() noexcept : m_value(0) {}
    constexpr BundleFlags(int value) noexcept : m_value(value) {}

    constexpr void setValue(int value) noexcept { m_value = value; }
    constexpr int value() const noexcept { return m_value; }

    constexpr CompressionType compression() const noexcept { return (CompressionType)(m_value & CompressionTypeMask); }
    constexpr bool isBlocksAndDirectoryInfoCombined() const noexcept { return (m_value & BlocksAndDirectoryInfoCombined) != 0; };
    constexpr bool isBlocksInfoAtTheEnd() const noexcept { return (m_value & BlocksInfoAtTheEnd) != 0; }
private:
    int m_value;
};
}

#endif // BUNDLEFLAGS_H
