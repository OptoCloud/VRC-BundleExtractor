#include "directoryinfo.h"

#include "bundlereader.h"

VRCE::BundleFiles::DirectoryInfo::DirectoryInfo() noexcept
    : m_nodes()
{
}

void VRCE::BundleFiles::DirectoryInfo::read(BundleFiles::BundleReader& reader)
{
    m_nodes = reader.readObjectVector<BundleFiles::Node>();
}
