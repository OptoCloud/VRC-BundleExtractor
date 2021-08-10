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

std::span<const VRCE::BundleFiles::Node> VRCE::BundleFiles::DirectoryInfo::nodes() const noexcept
{
    return m_nodes;
}
