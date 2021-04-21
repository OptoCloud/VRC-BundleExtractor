#ifndef READERHELPERS_H
#define READERHELPERS_H

#include <istream>
#include <span>

namespace VRCE::ReaderHelpers {
template <typename T>
inline T read_type(std::istream& stream)
{
    T type{};
    stream.read((char*)&type, sizeof(T));
    return type;
}
template <typename T>
inline void read_array(std::istream& stream, std::span<T> readInto)
{
    stream.read((char*)readInto.data(), readInto.size() * sizeof(T));
}
}

#endif // READERHELPERS_H
