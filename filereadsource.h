#ifndef FILEREADSOURCE_H
#define FILEREADSOURCE_H

#include "ireadsource.h"

#include <filesystem>
#include <istream>
#include <fstream>

namespace VRCE {

class FileReadSource : public VRCE::IReadSource
{
public:
    IReadSource::Type InterfaceType() const override;

    FileReadSource(const std::filesystem::path& path);

    bool isValid() const override;

    std::uint8_t get() override;
    void read(std::uint8_t* buf, std::size_t size) override;
    std::string readString() override;

    void seekBeg(std::ptrdiff_t offset) override;
    void seekRel(std::ptrdiff_t offset) override;

    std::ptrdiff_t position() const override;
private:
    std::shared_ptr<std::ifstream> m_stream;
};

}

#endif // FILEREADSOURCE_H
