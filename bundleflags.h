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

    BundleFlags() : m_value(0) {}
    BundleFlags(int value) : m_value(value) {}

    inline void setValue(int value) { m_value = value; }
    inline int value() const { return m_value; }

    constexpr CompressionType compression() const noexcept { return (CompressionType)(m_value & CompressionTypeMask); }
    constexpr bool isBlocksAndDirectoryInfoCombined() const noexcept { return (m_value & BlocksAndDirectoryInfoCombined) != 0; };
    constexpr bool isBlocksInfoAtTheEnd() const noexcept { return (m_value & BlocksInfoAtTheEnd) != 0; }
private:
    int m_value;
};
}

#endif // BUNDLEFLAGS_H
