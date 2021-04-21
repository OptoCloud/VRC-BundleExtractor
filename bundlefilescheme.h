#ifndef BUNDLEFILESCHEME_H
#define BUNDLEFILESCHEME_H

#include "bundleheader.h"

#include "fileschemelist.h"

#include <filesystem>

namespace VRCE {
class BundleFileScheme : public FileSchemeList
{
    BundleFileScheme(std::filesystem::path filePath);
public:
    static BundleFileScheme ReadScheme(std::filesystem::path filePath);

private:
    void readScheme(std::istream& stream);
    void readHeader(std::istream& stream);

    void readRawWebMetaData(std::istream& stream, std::vector<char>& dataBuf, std::int64_t& metadataOffset);
    void readFileStreamMetaData(std::istream& stream, std::int64_t basePosition);
    void readMetaData(std::istream& stream, std::int32_t metadataSize);
    void readRawWebData(std::istream& stream, std::int64_t metadataOffset);
    void readFileStreamData(std::istream& stream, std::int64_t basePosition, std::int64_t headerSize);

    BundleFiles::BundleHeader m_header;
};
}

#endif // BUNDLEFILESCHEME_H
