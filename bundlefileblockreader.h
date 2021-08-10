#ifndef BUNDLEFILEBLOCKREADER_H
#define BUNDLEFILEBLOCKREADER_H

#include "node.h"
#include "blocksinfo.h"
#include "binaryreader.h"

namespace VRCE::BundleFiles {

class BundleFileBlockReader
{
public:
    BundleFileBlockReader(VRCE::BinaryReader& reader, const BundleFiles::BlocksInfo& blocksInfo);

    BinaryReader readEntry(const BundleFiles::Node entry);
private:
    VRCE::BinaryReader m_reader;
    BundleFiles::BlocksInfo m_blocksInfo;
    std::int64_t m_dataOffset;

    std::shared_ptr<std::vector<std::uint8_t>> m_cachedBlock;
    VRCE::BinaryReader m_cachedBlockReader;
    int m_cachedBlockIndex = -1;
};

}

#endif // BUNDLEFILEBLOCKREADER_H
