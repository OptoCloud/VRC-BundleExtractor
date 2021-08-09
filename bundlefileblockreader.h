#ifndef BUNDLEFILEBLOCKREADER_H
#define BUNDLEFILEBLOCKREADER_H

#include "blocksinfo.h"
#include "binaryreader.h"

namespace VRCE::BundleFiles {

class BundleFileBlockReader : public VRCE::BinaryReader
{
public:
    BundleFileBlockReader(VRCE::BinaryReader& reader, BundleFiles::BlocksInfo& blocksInfo);
private:
    BundleFiles::BlocksInfo m_blocksInfo;
    std::int64_t m_dataOffset;


};

}

#endif // BUNDLEFILEBLOCKREADER_H
