#include "storageblocks.h"

#include "bundlereader.h"

VRCE::BundleFiles::StorageBlocks::StorageBlocks() noexcept
    : m_uncompressedSize(0)
    , m_compressedSize(0)
    , m_flags()
{
}

void VRCE::BundleFiles::StorageBlocks::read(VRCE::BundleFiles::BundleReader& reader)
{
    m_uncompressedSize = reader.read32u();
    m_compressedSize = reader.read32u();
    m_flags = reader.read16u();
}
