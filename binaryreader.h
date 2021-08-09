#ifndef BINARYREADER_H
#define BINARYREADER_H

#include "ireadsource.h"

#include <filesystem>
#include <span>
#include <memory>
#include <vector>
#include <istream>
#include <type_traits>

namespace VRCE {
class FileReadSource;
class MemoryReadSource;
class BinaryReader
{
public:
    BinaryReader(const std::filesystem::path& path);
    BinaryReader(std::shared_ptr<std::vector<std::uint8_t>> data);
    BinaryReader(const VRCE::BinaryReader& other);
    virtual ~BinaryReader();

    VRCE::IReadSource* readSource();
    bool isValid() const;
    std::ptrdiff_t position() const;
    void seekBeg(std::ptrdiff_t offset);
    void seekRel(std::ptrdiff_t offset);

    char readChar();
    bool readBool();

    std::int8_t  read8s();
    std::uint8_t read8u();

    virtual std::int16_t  read16s();
    virtual std::uint16_t read16u();

    virtual std::int32_t  read32s();
    virtual std::uint32_t read32u();

    virtual std::int64_t  read64s();
    virtual std::uint64_t read64u();

    virtual float  readFloat();
    virtual double readDouble();

    std::string readString();

    // virtual std::vector<bool> readBoolVector() = 0;

    virtual std::vector<std::int8_t>  read8sVector();
    virtual std::vector<std::uint8_t> read8uVector();

    virtual std::vector<std::int16_t>  read16sVector();
    virtual std::vector<std::uint16_t> read16uVector();

    virtual std::vector<std::int32_t>  read32sVector();
    virtual std::vector<std::uint32_t> read32uVector();

    virtual std::vector<std::int64_t>  read64sVector();
    virtual std::vector<std::uint64_t> read64uVector();

    virtual std::vector<float>  readFloatVector();
    virtual std::vector<double> readDoubleVector();

    void readInto(std::span<std::uint8_t> span);

    void alignStream();

    VRCE::BinaryReader& operator = (const VRCE::BinaryReader& other);
protected:
    VRCE::IReadSource* m_readsource;
};

template <class T>
concept implementsBinaryReader = std::is_base_of_v<BinaryReader, T>;
}

#endif // BINARYREADER_H
