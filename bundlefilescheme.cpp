#include "bundlefilescheme.h"

#include "bundlefileblockreader.h"
#include "filereadsource.h"
#include "memoryreadsource.h"
#include "bundlereader.h"
#include "vecstreambuf.h"
#include "endianreader.h"

#include "lz4.h"
#include "lz4hc.h"

#include "lzma.h"

#include <fstream>

using namespace VRCE::BundleFiles;

VRCE::BundleFileScheme::BundleFileScheme(std::filesystem::path filePath)
    : FileSchemeList(filePath)
    , m_header()
    , m_metadata()
{
}

VRCE::BundleFileScheme VRCE::BundleFileScheme::ReadScheme(std::filesystem::path filePath)
{
    BundleFileScheme scheme(filePath);

    VRCE::BinaryReader reader(filePath);

    if (!reader.isValid()) {
        throw ""; // File wont open or some shit
    }

    scheme.readScheme(reader);

    return scheme;
}

void VRCE::BundleFileScheme::readScheme(VRCE::BinaryReader& reader)
{
    std::int64_t basePosition = reader.position();

    readHeader(reader);

    switch (m_header.signature().value()) {
    case BundleType::UnityRaw:
    case BundleType::UnityWeb:
    {
        std::shared_ptr<std::vector<std::uint8_t>> data;

        std::int64_t metadataOffset = 0;

        readRawWebMetaData(reader, data, metadataOffset);

        VRCE::BinaryReader dataReader(data);
        readRawWebData(dataReader, metadataOffset);
        break;
    }
    case BundleType::UnityFS:
    {
        std::int64_t headerSize = reader.position() - basePosition;

        readFileStreamMetaData(reader, basePosition);
        readFileStreamData(reader, basePosition, headerSize);
        break;
    }
    default:
        throw "";// "Unknown bundle signature '{Header.Signature}'"
    }
}

void VRCE::BundleFileScheme::readHeader(VRCE::BinaryReader& reader)
{
    std::int64_t headerPosition = reader.position();

    VRCE::BundleFiles::BundleReader bundleReader(reader, VRCE::EndianType::BigEndian);

    m_header.read(bundleReader);

    if (m_header.signature().isRawWeb()) {
        if (reader.position() -  headerPosition != m_header.rawWeb()->headerSize())
        {
            throw ""; // "Read {reader.Position - headerPosition} but expected {Header.RawWeb.HeaderSize}"
        }
    }
}

void VRCE::BundleFileScheme::readRawWebMetaData(VRCE::BinaryReader& reader, std::shared_ptr<std::vector<std::uint8_t>>& dataBuf, std::int64_t& metadataOffset)
{
    auto header = m_header.rawWeb();

    std::int32_t metadataSize = 0;
    if (BundleRawWebHeader::HasUncompressedBlocksInfoSize(m_header.version())) {
        metadataSize = header->uncompressedBlocksInfoSize();
    }

    switch (m_header.signature().value()) {
    case BundleType::UnityRaw:
        break;
    case BundleType::UnityWeb:
        break;
    default:
        throw ""; // Exception($"Unsupported bundle signature '{Header.Signature}'");
    }
}

void VRCE::BundleFileScheme::readFileStreamMetaData(VRCE::BinaryReader& reader, std::int64_t basePosition)
{
    auto header = m_header.fileStream();

    if (header->flags().isBlocksInfoAtTheEnd())
    {
        reader.seekBeg(basePosition + (header->size() - header->compressedBlocksInfoSize()));
    }

    CompressionType metaCompression = header->flags().compression();
    switch (metaCompression) {
    case CompressionType::None:
    {
        readMetaData(reader, header->uncompressedBlocksInfoSize());
        break;
    }
    case CompressionType::Lzma:
    {
        std::vector<std::uint8_t> compressedData(header->compressedBlocksInfoSize());
        auto uncompressedData = std::make_shared<std::vector<std::uint8_t>>(header->uncompressedBlocksInfoSize());

        reader.readSource()->read(compressedData.data(), compressedData.size());

        // TODO: lzma decompression

        // Parse it
        VRCE::BinaryReader uncompressedDataReader(uncompressedData);
        readMetaData(uncompressedDataReader, header->uncompressedBlocksInfoSize());
        break;
    }
    case CompressionType::Lz4:
    case CompressionType::Lz4HC:
    {
        std::vector<std::uint8_t> compressedData(header->compressedBlocksInfoSize());
        auto uncompressedData = std::make_shared<std::vector<std::uint8_t>>(header->uncompressedBlocksInfoSize());

        reader.readSource()->read(compressedData.data(), compressedData.size());

        // DeCompress (TODO: loop until all is read) ((POSSIBLE BUG))
        int result = LZ4_decompress_safe((char*)compressedData.data(), (char*)uncompressedData->data(), compressedData.size(), header->uncompressedBlocksInfoSize());

        if (result != header->uncompressedBlocksInfoSize()) {
            throw ""; // Decompression failed...
        }

        // Parse it
        VRCE::BinaryReader uncompressedDataReader(uncompressedData);
        readMetaData(uncompressedDataReader, header->uncompressedBlocksInfoSize());
        break;
    }
    default:
        throw ""; // NotSupportedException($"Bundle compression '{metaCompression}' isn't supported");
    }
}

void VRCE::BundleFileScheme::readMetaData(VRCE::BinaryReader& reader, std::int32_t metadataSize)
{
    std::int64_t metadataPosition = reader.position();

    BundleReader bundleReader(reader, EndianType::BigEndian, m_header.signature(), m_header.version(), m_header.flags());

    m_metadata.read(bundleReader);

    if (metadataSize > 0)
    {
        if (reader.position() - metadataPosition != metadataSize)
        {
            throw "";// new Exception($"Read {stream.Position - metadataPosition} but expected {metadataSize}");
        }
    }
}

void VRCE::BundleFileScheme::readRawWebData(VRCE::BinaryReader& reader, std::int64_t metadataOffset)
{

}

void VRCE::BundleFileScheme::readFileStreamData(VRCE::BinaryReader& reader, std::int64_t basePosition, std::int64_t headerSize)
{
    if (m_header.fileStream()->flags().isBlocksInfoAtTheEnd()) {
        reader.seekBeg(basePosition + headerSize);
    }

    BundleFileBlockReader blockReader(reader, m_metadata.blocksInfo());

    for (const auto& entry : m_metadata.directoryInfo().nodes()) {
        VRCE::BinaryReader entryReader = blockReader.readEntry(entry);
        //VRCE::FileScheme scheme = G
    }
}
