#ifndef BLOCKSINFO_H
#define BLOCKSINFO_H

#include "hash128.h"
#include "storageblock.h"
#include "ibundlereadable.h"

#include <span>
#include <vector>

namespace VRCE::BundleFiles {
class BlocksInfo : public IBundleReadable
{
public:
    BlocksInfo() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;

    std::span<const StorageBlock> storageBlocks() const noexcept;
private:
    VRCE::Classes::Misc::Hash128 m_hash;
    std::vector<StorageBlock> m_storageblocks;
};
}

#endif // BLOCKSINFO_H
