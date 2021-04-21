#ifndef COMPRESSIONTYPE_H
#define COMPRESSIONTYPE_H

namespace VRCE::BundleFiles {
enum class CompressionType
{
    None	= 0,
    Lzma	= 1,
    Lz4		= 2,
    Lz4HC	= 3,
    Lzham	= 4,
};
}

#endif // COMPRESSIONTYPE_H
