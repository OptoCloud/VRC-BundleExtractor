#include "storageblock.h"

#include "bundlereader.h"

VRCE::BundleFiles::StorageBlock::StorageBlock() noexcept
    : m_uncompressedSize(0)
    , m_compressedSize(0)
    , m_flags()
{
}

void VRCE::BundleFiles::StorageBlock::read(VRCE::BundleFiles::BundleReader& reader)
{
    m_uncompressedSize = reader.read32u();
    m_compressedSize = reader.read32u();
    m_flags.setValue(reader.read16u());
}

std::uint32_t VRCE::BundleFiles::StorageBlock::uncompressedSize() const noexcept
{
    return m_uncompressedSize;
}

std::uint32_t VRCE::BundleFiles::StorageBlock::compressedSize() const noexcept
{
    return m_compressedSize;
}

VRCE::BundleFiles::StorageBlockFlags VRCE::BundleFiles::StorageBlock::flags() const noexcept
{
    return m_flags;
}
