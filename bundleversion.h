#ifndef BUNDLEVERSION_H
#define BUNDLEVERSION_H

namespace VRCE::BundleFiles {
enum class BundleVersion
{
    Unknown     = 0,

    BF_100_250	= 1,
    BF_260_340	= 2,
    BF_350_4x	= 3,
    BF_520a1	= 4,
    BF_520aunk	= 5,
    BF_520_x	= 6,
};
}

#endif // BUNDLEVERSION_H
