#ifndef BLOCKSINFO_H
#define BLOCKSINFO_H

#include "hash128.h"
#include "storageblocks.h"
#include "ibundlereadable.h"

#include <vector>

namespace VRCE::BundleFiles {
class BlocksInfo : public IBundleReadable
{
public:
    BlocksInfo() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;
private:
    VRCE::Classes::Misc::Hash128 m_hash;
    std::vector<StorageBlocks> m_storageblocks;
};
}

#endif // BLOCKSINFO_H
