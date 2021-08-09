#ifndef BUNDLEFILESTREAMHEADER_H
#define BUNDLEFILESTREAMHEADER_H

#include "bundleflags.h"
#include "endianreader.h"

namespace VRCE::BundleFiles {
class BundleFileStreamHeader
{
public:
    void read(BinaryReader& reader);

    std::int64_t size() const;
    std::int32_t compressedBlocksInfoSize() const;
    std::int32_t uncompressedBlocksInfoSize() const;
    BundleFlags flags() const;
private:
    std::int64_t m_size;
    std::int32_t m_compressedBlocksInfoSize;
    std::int32_t m_uncompressedBlocksInfoSize;
    BundleFlags m_flags;

};
}

#endif // BUNDLEFILESTREAMHEADER_H
