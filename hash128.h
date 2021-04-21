#ifndef HASH128_H
#define HASH128_H

#include "ibinaryreader.h"
#include "ibundlereadable.h"

#include "version.h"

#include <string_view>
#include <cstdint>

namespace VRCE::Classes::Misc {
struct Hash128 : public IBundleReadable
{
public:
    static int ToSerializedVersion(Version version);

    Hash128();
    Hash128(std::uint32_t v);
    Hash128(std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3);

    void read(IBinaryReader& reader) override;

    std::uint32_t data0() const;
    std::uint32_t data1() const;
    std::uint32_t data2() const;
    std::uint32_t data3() const;
private:
    std::uint32_t m_data0;
    std::uint32_t m_data1;
    std::uint32_t m_data2;
    std::uint32_t m_data3;
public:
    static constexpr std::string_view Bytes0Name = "bytes[0]";
    static constexpr std::string_view Bytes1Name = "bytes[1]";
    static constexpr std::string_view Bytes2Name = "bytes[2]";
    static constexpr std::string_view Bytes3Name = "bytes[3]";
    static constexpr std::string_view Bytes4Name = "bytes[4]";
    static constexpr std::string_view Bytes5Name = "bytes[5]";
    static constexpr std::string_view Bytes6Name = "bytes[6]";
    static constexpr std::string_view Bytes7Name = "bytes[7]";
    static constexpr std::string_view Bytes8Name = "bytes[8]";
    static constexpr std::string_view Bytes9Name = "bytes[9]";
    static constexpr std::string_view Bytes10Name = "bytes[10]";
    static constexpr std::string_view Bytes11Name = "bytes[11]";
    static constexpr std::string_view Bytes12Name = "bytes[12]";
    static constexpr std::string_view Bytes13Name = "bytes[13]";
    static constexpr std::string_view Bytes14Name = "bytes[14]";
    static constexpr std::string_view Bytes15Name = "bytes[15]";
    static constexpr std::string_view HashName = "Hash";
};
}

#endif // HASH128_H
