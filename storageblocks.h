#ifndef STORAGEBLOCKS_H
#define STORAGEBLOCKS_H

#include "ibundlereadable.h"

namespace VRCE::BundleFiles {
class StorageBlocks : public IBundleReadable
{
public:
    enum Flags : std::uint16_t {
        None                = 0x0000,
        CompressionTypeMask = 0x003F,
        Streamed			= 0x0040,
    };

    StorageBlocks() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;
private:
    std::uint32_t m_uncompressedSize;
    std::uint32_t m_compressedSize;
    std::uint16_t m_flags;
};
}

#endif // STORAGEBLOCKS_H
