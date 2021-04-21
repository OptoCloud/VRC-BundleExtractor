#include "bundlefilescheme.h"

#include "vecstreambuf.h"
#include "endianreader.h"

#include "lz4.h"
#include "lz4hc.h"

#include "lzma.h"

#include <fstream>

using namespace VRCE::BundleFiles;

VRCE::BundleFileScheme::BundleFileScheme(std::filesystem::path filePath)
    : FileSchemeList(filePath)
{

}

VRCE::BundleFileScheme VRCE::BundleFileScheme::ReadScheme(std::filesystem::path filePath)
{
    BundleFileScheme scheme(filePath);

    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw ""; // File wont open or some shit
    }

    scheme.readScheme(file);

    return scheme;
}

void VRCE::BundleFileScheme::readScheme(std::istream& stream)
{
    std::int64_t basePosition = (std::int64_t)stream.tellg();

    readHeader(stream);

    switch (m_header.signature().value()) {
    case BundleType::UnityRaw:
    case BundleType::UnityWeb:
    {
        std::vector<char> data;

        std::int64_t metadataOffset = 0;

        readRawWebMetaData(stream, data, metadataOffset);

        VecStreamBuf<char> dataBuf(data);
        std::istream dataStream(&dataBuf);

        readRawWebData(dataStream, metadataOffset);
        break;
    }
    case BundleType::UnityFS:
    {
        std::int64_t headerSize = (std::int64_t)stream.tellg() - basePosition;

        readFileStreamMetaData(stream, basePosition);
        readFileStreamData(stream, basePosition, headerSize);
        break;
    }
    default:
        throw "";// "Unknown bundle signature '{Header.Signature}'"
    }
}

void VRCE::BundleFileScheme::readHeader(std::istream& stream)
{
    std::int64_t headerPosition = (std::int64_t)stream.tellg();

    VRCE::EndianReader reader(stream, VRCE::EndianType::BigEndian);

    m_header.read(reader);

    if (m_header.signature().isRawWeb()) {
        if ((std::int64_t)stream.tellg() -  headerPosition != m_header.rawWeb()->headerSize())
        {
            throw ""; // "Read {stream.Position - headerPosition} but expected {Header.RawWeb.HeaderSize}"
        }
    }
}

void VRCE::BundleFileScheme::readRawWebMetaData(std::istream& stream, std::vector<char>& dataBuf, std::int64_t& metadataOffset)
{
    auto header = m_header.rawWeb();

    std::int32_t metadataSize = 0;
    if (BundleRawWebHeader::HasUncompressedBlocksInfoSize(header->version())) {
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

void VRCE::BundleFileScheme::readFileStreamMetaData(std::istream& stream, std::int64_t basePosition)
{
    auto header = m_header.fileStream();

    if (header->flags().isBlocksInfoAtTheEnd())
    {
        stream.seekg(basePosition + (header->size() - header->compressedBlocksInfoSize()));
    }

    CompressionType metaCompression = header->flags().compression();
    switch (metaCompression) {
    case CompressionType::None:
    {
        readMetaData(stream, header->uncompressedBlocksInfoSize());
        break;
    }
    case CompressionType::Lzma:
    {
        std::vector<char> uncompressedData(header->uncompressedBlocksInfoSize());
        VecStreamBuf<char> uncompressedDataBuf(uncompressedData);
        std::istream uncompressedDataStream(&uncompressedDataBuf);

        std::vector<char> compressedData(header->compressedBlocksInfoSize());
        stream.read(compressedData.data(), compressedData.size());

        // TODO: lzma decompression

        break;
    }
    case CompressionType::Lz4:
    case CompressionType::Lz4HC:
    {
        std::vector<char> uncompressedData(header->uncompressedBlocksInfoSize());
        VecStreamBuf<char> uncompressedDataBuf(uncompressedData);
        std::istream uncompressedDataStream(&uncompressedDataBuf);

        std::vector<char> compressedData(header->compressedBlocksInfoSize());
        stream.read(compressedData.data(), compressedData.size());

        int result = LZ4_decompress_safe(compressedData.data(), (char*)uncompressedData.data(), compressedData.size(), uncompressedData.size());

        if ((std::size_t)result != uncompressedData.size()) {
            throw ""; // Decompression failed...
        }

        readMetaData(uncompressedDataStream, uncompressedData.size());
        break;
    }
    default:
        throw ""; // NotSupportedException($"Bundle compression '{metaCompression}' isn't supported");
    }
}

void VRCE::BundleFileScheme::readMetaData(std::istream& stream, std::int32_t metadataSize)
{
    std::int64_t metadataPosition = (std::int64_t)stream.tellg();
}

void VRCE::BundleFileScheme::readRawWebData(std::istream& stream, std::int64_t metadataOffset)
{

}

void VRCE::BundleFileScheme::readFileStreamData(std::istream& stream, std::int64_t basePosition, std::int64_t headerSize)
{

}
