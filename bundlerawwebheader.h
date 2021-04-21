#ifndef BUNDLERAWWEBHEADER_H
#define BUNDLERAWWEBHEADER_H

#include "bundleversion.h"
#include "ibundlereadable.h"
#include "bundlescene.h"
#include "hash128.h"

#include <vector>
#include <cstdint>

namespace VRCE::BundleFiles {
class BundleRawWebHeader : public IBundleReadable
{
public:
    static bool HasHash(BundleVersion generation) noexcept;
    static bool HasCompleteFileSize(BundleVersion generation) noexcept;
    static bool HasUncompressedBlocksInfoSize(BundleVersion generation) noexcept;

    BundleRawWebHeader();

    void read(IBinaryReader& reader) override;

    std::int32_t headerSize() const;
    std::int32_t uncompressedBlocksInfoSize() const;
private:
    std::uint32_t m_crc;
    std::uint32_t m_minimumStreamedBytes;
    std::int32_t m_headerSize;
    std::int32_t m_numberOfScenesToDownloadBeforeStreaming;
    std::vector<BundleScene> m_scenes;
    std::uint32_t m_completeFileSize;
    std::int32_t m_uncompressedBlocksInfoSize;
    Classes::Misc::Hash128 m_hash;
};
}

#endif // BUNDLERAWWEBHEADER_H
