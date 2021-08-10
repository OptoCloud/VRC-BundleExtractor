#ifndef SEVENZIPHELPER_H
#define SEVENZIPHELPER_H

#include "binaryreader.h"

#include <span>
#include <cstdint>

namespace VRCE::SevenZipHelper {
bool DecompressLZMA(std::span<const std::uint8_t> compressedData, std::span<std::uint8_t> decompressedData);
bool DecompressLZMA(VRCE::BinaryReader& reader, std::size_t compressedSize, std::span<std::uint8_t> decompressedData);
}

#endif // SEVENZIPHELPER_H
