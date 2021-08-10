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
    virtual ~IBundleReadable(){};
    virtual void read(VRCE::BundleFiles::BundleReader& reader) = 0;
};

template <class T>
concept implementsBundleReadable = std::is_base_of_v<IBundleReadable, T>;

}

#endif // IBUNDLEREADABLE_H
