#ifndef BUNDLESCENE_H
#define BUNDLESCENE_H

#include "ibundlereadable.h"

#include <string>
#include <cstdint>

namespace VRCE::BundleFiles {
class BundleScene : public IBundleReadable
{
public:
    void read(IBinaryReader& reader) override;

    std::uint32_t compressedSize() const;
    std::uint32_t decompressedSize() const;

    std::string toString() const;
private:
    std::uint32_t m_compressedSize;
    std::uint32_t m_decompressedSize;
};
}

#endif // BUNDLESCENE_H
