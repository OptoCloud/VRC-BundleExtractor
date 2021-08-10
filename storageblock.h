#ifndef STORAGEBLOCKS_H
#define STORAGEBLOCKS_H

#include "storageblockflags.h"
#include "ibundlereadable.h"

namespace VRCE::BundleFiles {
class StorageBlock : public IBundleReadable
{
public:
    enum Flags : std::uint16_t {
        None                = 0x0000,
        CompressionTypeMask = 0x003F,
        Streamed			= 0x0040,
    };

    StorageBlock() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;

    std::uint32_t uncompressedSize() const noexcept;
    std::uint32_t compressedSize() const noexcept;
    StorageBlockFlags flags() const noexcept;
private:
    std::uint32_t m_uncompressedSize;
    std::uint32_t m_compressedSize;
    StorageBlockFlags m_flags;
};
}

#endif // STORAGEBLOCKS_H
