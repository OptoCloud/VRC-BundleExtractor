#ifndef IBUNDLEREADABLE_H
#define IBUNDLEREADABLE_H

#include "bundletype.h"
#include "bundleversion.h"
#include "bundleflags.h"

#include <type_traits>

namespace VRCE::BundleFiles {

class BundleReader;
class IBundleReadable
{
public:
    IBundleReadable() : m_signature(), m_version(), m_flags() {}
    IBundleReadable(const IBundleReadable& other) : m_signature(other.m_signature), m_version(other.m_version), m_flags(other.m_flags) {}
    virtual ~IBundleReadable(){};
    virtual void read(VRCE::BundleFiles::BundleReader& reader) = 0;

    constexpr void setSignature(BundleFiles::BundleType signature) { m_signature = signature; }
    constexpr BundleFiles::BundleType signature() const { return m_signature; }

    constexpr void setVersion(BundleFiles::BundleVersion version) { m_version = version; }
    constexpr BundleFiles::BundleVersion version() const { return m_version; }

    constexpr void setFlags(BundleFiles::BundleFlags flags) { m_flags = flags; }
    constexpr BundleFiles::BundleFlags flags() const { return m_flags; }
protected:
    BundleFiles::BundleType m_signature;
    BundleFiles::BundleVersion m_version;
    BundleFiles::BundleFlags m_flags;
};

template <class T>
concept implementsBundleReadable = std::is_base_of_v<IBundleReadable, T>;

}

#endif // IBUNDLEREADABLE_H
