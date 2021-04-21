#ifndef IBINARYREADER_H
#define IBINARYREADER_H

#include <span>
#include <vector>
#include <istream>
#include <type_traits>

namespace VRCE {
class IBinaryReader
{
public:
    IBinaryReader(std::istream& stream);
    virtual ~IBinaryReader(){};

    std::istream& stream();;

    char readChar();
    bool readBool();

    std::int8_t  read8s();
    std::uint8_t read8u();

    virtual std::int16_t  read16s() = 0;
    virtual std::uint16_t read16u() = 0;

    virtual std::int32_t  read32s() = 0;
    virtual std::uint32_t read32u() = 0;

    virtual std::int64_t  read64s() = 0;
    virtual std::uint64_t read64u() = 0;

    virtual float  readFloat() = 0;
    virtual double readDouble() = 0;

    std::string readString();

    // virtual std::vector<bool> readBoolVector() = 0;

    virtual std::vector<std::int8_t>  read8sVector() = 0;
    virtual std::vector<std::uint8_t> read8uVector() = 0;

    virtual std::vector<std::int16_t>  read16sVector() = 0;
    virtual std::vector<std::uint16_t> read16uVector() = 0;

    virtual std::vector<std::int32_t>  read32sVector() = 0;
    virtual std::vector<std::uint32_t> read32uVector() = 0;

    virtual std::vector<std::int64_t>  read64sVector() = 0;
    virtual std::vector<std::uint64_t> read64uVector() = 0;

    virtual std::vector<float>  readFloatVector() = 0;
    virtual std::vector<double> readDoubleVector() = 0;

    void readInto(std::span<std::uint8_t> span);

    void alignStream();

    IBinaryReader(IBinaryReader&) = delete;
    IBinaryReader& operator=(IBinaryReader&) = delete;
protected:
    std::istream& m_stream;
};

template <class T>
concept implementsBinaryReader = std::is_base_of_v<IBinaryReader, T>;
}

#endif // IBINARYREADER_H
