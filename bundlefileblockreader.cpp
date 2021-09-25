#include "bundlefileblockreader.h"

#include "sevenziphelper.h"

VRCE::BundleFiles::BundleFileBlockReader::BundleFileBlockReader(VRCE::BinaryReader& reader, const VRCE::BundleFiles::BlocksInfo& blocksInfo)
    : m_reader(reader)
    , m_blocksInfo(blocksInfo)
    , m_dataOffset(reader.position())
    , m_cachedBlock(std::make_shared<std::vector<std::uint8_t>>())
    , m_cachedBlockReader(m_cachedBlock)
    , m_cachedBlockIndex(-1)
{
}

VRCE::BinaryReader VRCE::BundleFiles::BundleFileBlockReader::readEntry(const VRCE::BundleFiles::Node entry)
{
    std::int32_t blockIndex = 0;
    std::int64_t blockCompressedOffset = 0;
    std::int64_t blockDecompressedOffset = 0;

    auto storageBlocks = m_blocksInfo.storageBlocks();

    while (blockCompressedOffset + storageBlocks[blockIndex].uncompressedSize() <= entry.offset()) {
        blockCompressedOffset += storageBlocks[blockIndex].compressedSize();
        blockDecompressedOffset += storageBlocks[blockIndex].uncompressedSize();
        blockIndex++;
    }

    std::int64_t entryOffsetInsideBlock = entry.offset() - blockDecompressedOffset;

    auto entryBuffer = std::make_shared<std::vector<std::uint8_t>>();
    entryBuffer->resize(entry.size());
    auto entryBufferIt = entryBuffer->begin();

    std::int64_t sizeLeft = entry.size();
    m_reader.seekBeg(m_dataOffset + blockCompressedOffset);

    while (sizeLeft > 0) {
        std::int64_t blockReaderOffset;
        VRCE::BinaryReader* blockReader;
        BundleFiles::StorageBlock block = storageBlocks[blockIndex];

        if (m_cachedBlockIndex == blockIndex) {
            blockReaderOffset = 0;
            blockReader = &m_cachedBlockReader;
            m_reader.seekRel(block.compressedSize());
        }
        else {
            BundleFiles::CompressionType compressType = block.flags().compression();
            if (compressType == BundleFiles::CompressionType::None) {
                blockReaderOffset = m_dataOffset + blockCompressedOffset;
                blockReader = &m_reader;
            }
            else {
                blockReaderOffset = 0;
                m_cachedBlockIndex = blockIndex;
                m_cachedBlock->resize(block.uncompressedSize());
                m_cachedBlockReader.seekBeg(0);

                switch (compressType) {
                case BundleFiles::CompressionType::Lzma:
                    if (!SevenZipHelper::DecompressLZMA(m_reader, block.compressedSize(), *m_cachedBlock)) {
                        throw std::exception("Failed to decompress LZMA Stream");
                    }
                    break;
                case BundleFiles::CompressionType::Lz4:
                case BundleFiles::CompressionType::Lz4HC:
                {/*
                    std::vector<std::uint8_t> compressedData(block.compressedSize());

                    m_reader.readInto(compressedData);

                    // DeCompress (TODO: loop until all is read) ((POSSIBLE BUG))
                    int result = LZ4_decompress_safe((char*)compressedData.data(), (char*)m_cachedBlock->data(), block.compressedSize(), block.uncompressedSize());

                    if (result != block.uncompressedSize()) {
                        throw ""; // Decompression failed...
                    }
*/
                    break;
                }
                default:
                    throw ""; // NotImplementedException($"Bundle compression '{compressType}' isn't supported");
                }
                blockReader = &m_cachedBlockReader;
            }
        }

        std::int64_t blockSize = block.uncompressedSize() - entryOffsetInsideBlock;
        blockReader->seekBeg(blockReaderOffset + entryOffsetInsideBlock);
        entryOffsetInsideBlock = 0;

        std::int64_t sizeRead = std::min(blockSize, sizeLeft);
        blockReader->readInto(std::span<std::uint8_t>(entryBufferIt, entryBufferIt + sizeRead));
        entryBufferIt += sizeRead;
        blockIndex++;

        blockCompressedOffset += block.compressedSize();
        sizeLeft -= sizeRead;
    }

    return VRCE::BinaryReader(entryBuffer);
}
