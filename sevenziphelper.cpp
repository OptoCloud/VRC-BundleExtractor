#include "sevenziphelper.h"

#include "lzma.h"

#include <mutex>
#include <array>
#include <thread>
#include <unordered_map>

std::mutex l_threadCache{};
std::unordered_map<std::thread::id, std::shared_ptr<std::vector<std::uint8_t>>> s_threadCache;
inline std::shared_ptr<std::vector<std::uint8_t>> GetBuffer()
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
        lzma_end(&lzmaStream);
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
            lzma_end(&lzmaStream);
            return false;
        }

        std::size_t written = sizeLeft - lzmaStream.avail_out;
        dataIt += written;
        sizeLeft -= written;
    } while (sizeLeft != 0);

    lzma_code(&lzmaStream, LZMA_FINISH);

    lzma_end(&lzmaStream);

    return true;
}

// TODO: FIXME, not fully integrated
bool VRCE::SevenZipHelper::DecompressLZMA(VRCE::BinaryReader& reader, std::size_t compressedSize, std::span<std::uint8_t> decompressedData)
{
    lzma_stream lzmaStream = LZMA_STREAM_INIT;

    lzma_ret rv = lzma_stream_decoder(&lzmaStream, UINT64_MAX, LZMA_TELL_UNSUPPORTED_CHECK);

    if (rv != LZMA_OK) {
        lzma_end(&lzmaStream);
        return false;
    }

    auto& buffer = *GetBuffer();

    std::uint8_t* decompressedIt = decompressedData.data();
    std::size_t decompressedLeft = decompressedData.size();

    lzmaStream.next_in = nullptr;
    lzmaStream.avail_in = 0;
    lzmaStream.next_out = decompressedIt;
    lzmaStream.avail_out = decompressedLeft;

    lzma_action action = LZMA_RUN;

    while (true) {
        if (lzmaStream.avail_in == 0) {
            buffer.resize(std::min((std::size_t)BUFSIZ, compressedSize));
            reader.readInto(buffer);

            lzmaStream.next_in = buffer.data();
            lzmaStream.avail_in = buffer.size();

            if (buffer.size() != BUFSIZ) {
                action = LZMA_FINISH;
            }
        }

        rv = lzma_code(&lzmaStream, action);

        if (lzmaStream.avail_out == 0 || rv == LZMA_STREAM_END) {
            std::size_t writeSize = decompressedLeft - lzmaStream.avail_out;
            decompressedIt += writeSize;
            decompressedLeft -= writeSize;
        }

        if (rv != LZMA_OK) {
            return rv == LZMA_STREAM_END;
        }

    };
}
