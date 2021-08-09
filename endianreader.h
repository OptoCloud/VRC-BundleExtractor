#ifndef ENIANREADER_H
#define ENIANREADER_H

#include "endiantype.h"
#include "binaryreader.h"

#include <vector>
#include <istream>
#include <cstdint>

namespace VRCE {
class EndianReader : public BinaryReader {
public:
    static EndianType ComputerEndianess() noexcept;

    EndianReader(const VRCE::BinaryReader& reader, EndianType endianess);

    EndianType endianess() const noexcept;

    std::int16_t  read16s() override;
    std::uint16_t read16u() override;

    std::int32_t  read32s() override;
    std::uint32_t read32u() override;

    std::int64_t  read64s() override;
    std::uint64_t read64u() override;

    float  readFloat() override;
    double readDouble() override;

    std::vector<std::int8_t>  read8sVector() override;
    std::vector<std::uint8_t> read8uVector() override;

    std::vector<std::int16_t>  read16sVector() override;
    std::vector<std::uint16_t> read16uVector() override;

    std::vector<std::int32_t>  read32sVector() override;
    std::vector<std::uint32_t> read32uVector() override;

    std::vector<std::int64_t>  read64sVector() override;
    std::vector<std::uint64_t> read64uVector() override;

    std::vector<float>  readFloatVector() override;
    std::vector<double> readDoubleVector() override;
private:
    bool m_differentEndianess;
};
}

#endif // ENIANREADER_H
