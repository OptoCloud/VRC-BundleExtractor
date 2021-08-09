#ifndef READERHELPERS_H
#define READERHELPERS_H

#include "ireadsource.h"
#include <memory>
#include <span>

namespace VRCE::ReaderHelpers {
template <typename T>
inline T read_type(VRCE::IReadSource* readsource)
{
    T type;
    readsource->read((std::uint8_t*)&type, sizeof(T));
    return type;
}
template <typename T>
inline void read_array(VRCE::IReadSource* readsource, std::span<T> readInto)
{
    readsource->read((std::uint8_t*)readInto.data(), readInto.size() * sizeof(T));
}
}

#endif // READERHELPERS_H
