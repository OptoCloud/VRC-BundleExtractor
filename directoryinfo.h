#ifndef DIRECTORYINFO_H
#define DIRECTORYINFO_H

#include "node.h"
#include "ibundlereadable.h"
#include "bundletype.h"

#include <span>
#include <vector>

namespace VRCE::BundleFiles {

class DirectoryInfo : BundleFiles::IBundleReadable
{
public:
    DirectoryInfo() noexcept;

    void read(BundleFiles::BundleReader &reader) override;

    std::span<const BundleFiles::Node> nodes() const noexcept;
private:
    std::vector<BundleFiles::Node> m_nodes;
};

}

#endif // DIRECTORYINFO_H
