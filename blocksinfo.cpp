#include "blocksinfo.h"

#include "bundlereader.h"

VRCE::BundleFiles::BlocksInfo::BlocksInfo() noexcept
{
}

void VRCE::BundleFiles::BlocksInfo::read(VRCE::BundleFiles::BundleReader& reader)
{
    m_hash.read(reader);
    m_storageblocks =  reader.readObjectVector<StorageBlock>();
}

std::span<const VRCE::BundleFiles::StorageBlock> VRCE::BundleFiles::BlocksInfo::storageBlocks() const noexcept
{
    return m_storageblocks;
}
