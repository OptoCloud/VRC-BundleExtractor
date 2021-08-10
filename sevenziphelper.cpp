#include "sevenziphelper.h"

#include "lzma.h"

#include <mutex>
#include <array>
#include <thread>
#include <memory>
#include <unordered_map>

std::mutex l_threadCache{};
std::unordered_map<std::thread::id, std::shared_ptr<std::vector<std::uint8_t>>> s_threadCache;
std::shared_ptr<std::vector<std::uint8_t>> GetBuffer()
{
    std::thread::id threadId = std::this_thread::get_id();

    std::scoped_lock l(l_threadCache);

    auto it = s_threadCache.find(threadId);

    if (it == s_threadCache.end()) {
        auto buffer = std::make_shared<std::vector<std::uint8_t>>();
        s_threadCache[threadId] = buffer;
        return buffer;
    }

    return it->second;
}

// TODO: FIXME, not fully integrated
bool VRCE::SevenZipHelper::DecompressLZMA(std::span<const std::uint8_t> compressedData, std::span<std::uint8_t> decompressedData)
{
    lzma_stream lzmaStream = LZMA_STREAM_INIT;

    lzma_ret rv = lzma_stream_decoder(&lzmaStream, UINT64_MAX, LZMA_TELL_UNSUPPORTED_CHECK | LZMA_CONCATENATED);

    if (rv != LZMA_OK) {
        return false;
    }

    lzmaStream.next_in = compressedData.data();
    lzmaStream.avail_in = compressedData.size();

    std::uint8_t* dataIt = decompressedData.data();
    std::size_t sizeLeft = decompressedData.size();

    do {
        lzmaStream.next_out = dataIt;
        lzmaStream.avail_out = sizeLeft;

        rv = lzma_code(&lzmaStream, LZMA_FINISH);

        if (rv != LZMA_OK) {
            return false;
        }

        std::size_t written = sizeLeft - lzmaStream.avail_out;
        dataIt += written;
        sizeLeft -= written;
    } while (sizeLeft != 0);

    lzma_end(&lzmaStream);

    return true;
}

// TODO: FIXME, not fully integrated
bool VRCE::SevenZipHelper::DecompressLZMA(VRCE::BinaryReader& reader, std::size_t compressedSize, std::span<std::uint8_t> decompressedData)
{
    lzma_ret rv;
    lzma_block lzBlock;
    std::array<std::uint8_t, 5> header;

    reader.readInto(header);

    lzBlock.header_size = header.size();

    rv = lzma_block_header_decode(&lzBlock, nullptr, header.data());

    if (rv != LZMA_OK) {
        return false;
    }

    auto buffer = GetBuffer();
    buffer->resize(compressedSize - header.size());
    reader.readInto(*buffer);

    std::size_t posIn = 0;
    std::size_t posOut = 0;
    rv = lzma_block_buffer_decode(&lzBlock, nullptr, buffer->data(), &posIn, buffer->size(), decompressedData.data(), &posOut, decompressedData.size());

    return rv == LZMA_OK;
}
