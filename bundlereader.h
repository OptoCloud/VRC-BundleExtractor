#ifndef BUNDLEREADER_H
#define BUNDLEREADER_H

#include "ibinaryreader.h"
#include "ibundlereadable.h"

#include <vector>

namespace VRCE {
template <implementsBundleReadable T>
class ObjectReader
{
public:
    ObjectReader(IBinaryReader& reader)
        : m_reader(reader)
    {
    }

    T readObject()
    {
        T obj;
        obj.read(m_reader);
        return obj;
    }

    std::vector<T> readObjectVector()
    {
        std::int32_t vecSize = m_reader.read32s();

        std::vector<T> vec(vecSize);

        for (std::int32_t i = 0; i < vecSize; i++) {
            vec.emplace_back(readObject());
        }

        return vec;
    }
private:
    IBinaryReader& m_reader;
};
}

#endif // BUNDLEREADER_H
