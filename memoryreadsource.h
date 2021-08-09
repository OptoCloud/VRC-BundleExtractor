#ifndef MEMORYREADSOURCE_H
#define MEMORYREADSOURCE_H

#include "ireadsource.h"

#include <memory>
#include <vector>
#include <cstddef>

namespace VRCE {

class MemoryReadSource : public VRCE::IReadSource
{
public:
    IReadSource::Type InterfaceType() const override;

    MemoryReadSource(std::shared_ptr<const std::vector<std::uint8_t>> data);

    bool isValid() const override { return true; }

    std::uint8_t get() override;
    void read(std::uint8_t* buf, std::size_t size) override;
    std::string readString() override;

    void seekBeg(std::ptrdiff_t offset) override;
    void seekRel(std::ptrdiff_t offset) override;

    std::ptrdiff_t position() const override;
private:
    std::shared_ptr<const std::vector<std::uint8_t>> m_data;
    std::ptrdiff_t m_pos;
};

}

#endif // MEMORYREADSOURCE_H
