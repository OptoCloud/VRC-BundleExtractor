#include "bundlemetadata.h"

#include "bundlereader.h"

#include <fstream>

constexpr bool HasBlocksInfo(VRCE::BundleFiles::BundleType signature)
{
    return signature == VRCE::BundleFiles::BundleType::UnityFS;
}

VRCE::BundleFiles::BundleMetaData::BundleMetaData() noexcept
{
}

void VRCE::BundleFiles::BundleMetaData::read(VRCE::BundleFiles::BundleReader& reader)
{
    if (HasBlocksInfo(reader.signature())) {
        m_blocksInfo.read(reader);
        if (reader.flags().isBlocksAndDirectoryInfoCombined()) {
            m_directoryInfo.read(reader);
        }
    }
    else
    {
        reader.alignStream();
    }
}

const VRCE::BundleFiles::BlocksInfo& VRCE::BundleFiles::BundleMetaData::blocksInfo() const
{
    return m_blocksInfo;
}

const VRCE::BundleFiles::DirectoryInfo& VRCE::BundleFiles::BundleMetaData::directoryInfo() const
{
    return m_directoryInfo;
}
