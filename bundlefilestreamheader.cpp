#include "bundlefilestreamheader.h"

void VRCE::BundleFiles::BundleFileStreamHeader::read(VRCE::IBinaryReader& reader)
{
    m_size = reader.read64s();
    m_compressedBlocksInfoSize = reader.read32s();
    m_uncompressedBlocksInfoSize = reader.read32s();
    m_flags = (BundleFlags)reader.read32s();
}

std::int64_t VRCE::BundleFiles::BundleFileStreamHeader::size() const
{
    return m_size;
}

std::int32_t VRCE::BundleFiles::BundleFileStreamHeader::compressedBlocksInfoSize() const
{
    return m_compressedBlocksInfoSize;
}

std::int32_t VRCE::BundleFiles::BundleFileStreamHeader::uncompressedBlocksInfoSize() const
{
    return m_uncompressedBlocksInfoSize;
}

VRCE::BundleFiles::BundleFlags VRCE::BundleFiles::BundleFileStreamHeader::flags() const
{
    return m_flags;
}
