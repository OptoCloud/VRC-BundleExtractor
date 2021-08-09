#ifndef IREADSOURCE_H
#define IREADSOURCE_H

#include <string>
#include <cstdint>
#include <cstddef>

namespace VRCE {

class IReadSource
{
public:
    enum class Type {
        File,
        Memory,
    };
    virtual IReadSource::Type InterfaceType() const = 0;

    virtual ~IReadSource(){};

    virtual bool isValid() const { return false; }

    virtual std::uint8_t get() = 0;
    virtual void read(std::uint8_t* buf, std::size_t size) = 0;
    virtual std::string readString() = 0;

    virtual void seekBeg(std::ptrdiff_t offset) = 0;
    virtual void seekRel(std::ptrdiff_t offset) = 0;

    virtual std::ptrdiff_t position() const = 0;

    std::uint64_t refCount = 0;
};

}

#endif // IREADSOURCE_H
