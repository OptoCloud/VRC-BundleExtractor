#ifndef BUNDLEMETADATA_H
#define BUNDLEMETADATA_H

#include "blocksinfo.h"
#include "directoryinfo.h"
#include "ibundlereadable.h"

namespace VRCE::BundleFiles {
class BundleMetaData : public IBundleReadable
{
public:
    BundleMetaData() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;

    const VRCE::BundleFiles::BlocksInfo& blocksInfo() const;
    const VRCE::BundleFiles::DirectoryInfo& directoryInfo() const;
private:
    VRCE::BundleFiles::BlocksInfo m_blocksInfo;
    VRCE::BundleFiles::DirectoryInfo m_directoryInfo;

};
}

#endif // BUNDLEMETADATA_H
