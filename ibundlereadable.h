#ifndef IBUNDLEREADABLE_H
#define IBUNDLEREADABLE_H

#include "bundletype.h"
#include "bundleversion.h"
#include "bundleflags.h"

#include <type_traits>

namespace VRCE {
class IBinaryReader;
class IBundleReadable
{
public:
    virtual ~IBundleReadable(){};
    virtual void read(IBinaryReader& reader) = 0;

    inline void setVersion(BundleFiles::BundleVersion version) { m_version = version; }
    inline BundleFiles::BundleVersion version() const { return m_version; }
protected:
    BundleFiles::BundleType m_signature;
    BundleFiles::BundleVersion m_version;
    BundleFiles::BundleFlags m_flags;
};

template <class T>
concept implementsBundleReadable = std::is_base_of_v<IBundleReadable, T>;
}

#endif // IBUNDLEREADABLE_H
