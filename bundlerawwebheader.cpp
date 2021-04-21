#include "bundlerawwebheader.h"

#include "bundlereader.h"

bool VRCE::BundleFiles::BundleRawWebHeader::HasHash(VRCE::BundleFiles::BundleVersion generation) noexcept
{
    return generation >= BundleVersion::BF_520a1;
}

bool VRCE::BundleFiles::BundleRawWebHeader::HasCompleteFileSize(VRCE::BundleFiles::BundleVersion generation) noexcept
{
    return generation >= BundleVersion::BF_260_340;
}

bool VRCE::BundleFiles::BundleRawWebHeader::HasUncompressedBlocksInfoSize(VRCE::BundleFiles::BundleVersion generation) noexcept
{
    return generation >= BundleVersion::BF_350_4x;
}

VRCE::BundleFiles::BundleRawWebHeader::BundleRawWebHeader()
    : m_crc()
    , m_minimumStreamedBytes()
    , m_headerSize()
    , m_numberOfScenesToDownloadBeforeStreaming()
    , m_scenes()
    , m_completeFileSize()
    , m_uncompressedBlocksInfoSize()
    , m_hash()
{
}

void VRCE::BundleFiles::BundleRawWebHeader::read(VRCE::IBinaryReader& reader)
{
    if (HasHash(m_version)) {
        m_hash.read(reader);
        m_crc = reader.read32u();
    }

    m_minimumStreamedBytes = reader.read32u();
    m_headerSize = reader.read32s();
    m_numberOfScenesToDownloadBeforeStreaming = reader.read32s();
    m_scenes = ObjectReader<BundleScene>(reader).readObjectVector();

    if (HasCompleteFileSize(m_version))
    {
        m_completeFileSize = reader.read32u();
    }

    if (HasUncompressedBlocksInfoSize(m_version))
    {
        m_uncompressedBlocksInfoSize = reader.read32s();
    }

    reader.alignStream();
}

std::int32_t VRCE::BundleFiles::BundleRawWebHeader::headerSize() const
{
    return m_headerSize;
}

int32_t VRCE::BundleFiles::BundleRawWebHeader::uncompressedBlocksInfoSize() const
{
    return m_uncompressedBlocksInfoSize;
}
