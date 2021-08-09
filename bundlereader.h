#ifndef BUNDLEREADER_H
#define BUNDLEREADER_H

#include "endianreader.h"
#include "ibundlereadable.h"
#include "bundletype.h"
#include "bundleversion.h"

#include <vector>

namespace VRCE::BundleFiles {

class BundleReader : public EndianReader
{
public:
    BundleReader(const VRCE::BinaryReader& reader, EndianType endianess)
        : EndianReader(reader, endianess)
        , m_signature()
        , m_generation()
        , m_flags()
    {
    }
    BundleReader(const VRCE::BinaryReader& reader, EndianType endianess, BundleFiles::BundleType signature, BundleFiles::BundleVersion generation, BundleFiles::BundleFlags flags)
        : EndianReader(reader, endianess)
        , m_signature(signature)
        , m_generation(generation)
        , m_flags(flags)
    {
    }

    template <implementsBundleReadable T>
    T readObject()
    {
        T obj;
        obj.read(*this);
        return obj;
    }

    template <implementsBundleReadable T>
    std::vector<T> readObjectVector()
    {
        std::int32_t vecSize = read32s(); // TODO: BUG: possible crash if negative number is read

        std::vector<T> vec(vecSize);

        for (std::int32_t i = 0; i < vecSize; i++) {
            vec[i].read(*this);
        }

        return vec;
    }

    BundleFiles::BundleType signature() const
    {
        return m_signature;
    }

    BundleFiles::BundleVersion generation() const
    {
        return m_generation;
    }

    BundleFiles::BundleFlags flags() const
    {
        return m_flags;
    }
private:
    BundleFiles::BundleType m_signature;
    BundleFiles::BundleVersion m_generation;
    BundleFiles::BundleFlags m_flags;
};

}

#endif // BUNDLEREADER_H
