#ifndef ENDIANSWAP_H
#define ENDIANSWAP_H

#include <array>
#include <bit>
#include <cstdint>
#include <algorithm>
#include <concepts>

namespace VRCE {
template <class T>
concept trivially_copyable = std::is_trivially_copyable_v<T>;

template <trivially_copyable T>
constexpr void endian_swap(T& value)
{
    auto bytes = std::bit_cast<std::array<char,sizeof(T)>>(value);
    std::reverse(std::begin(bytes), std::end(bytes));
    value = std::bit_cast<T>(bytes);
}

template <typename T>
constexpr T endian_swap_if(T value, bool swap)
{
    if (swap) {
        VRCE::endian_swap(value);
    }

    return value;
}
}

#endif // ENDIANSWAP_H
