#ifndef BUNDLEFILESCHEME_H
#define BUNDLEFILESCHEME_H

#include "bundleheader.h"
#include "bundlemetadata.h"

#include "fileschemelist.h"

#include <filesystem>

namespace VRCE {
class BundleFileScheme : public FileSchemeList
{
    BundleFileScheme(std::filesystem::path filePath);
public:
    static BundleFileScheme ReadScheme(std::filesystem::path filePath);

private:
    void readScheme(VRCE::BinaryReader& reader);
    void readHeader(VRCE::BinaryReader& reader);

    void readRawWebMetaData(VRCE::BinaryReader& reader, std::shared_ptr<std::vector<std::uint8_t>>& dataBuf, std::int64_t& metadataOffset);
    void readFileStreamMetaData(VRCE::BinaryReader& reader, std::int64_t basePosition);
    void readMetaData(VRCE::BinaryReader& reader, std::int32_t metadataSize);
    void readRawWebData(VRCE::BinaryReader& reader, std::int64_t metadataOffset);
    void readFileStreamData(VRCE::BinaryReader& reader, std::int64_t basePosition, std::int64_t headerSize);

    BundleFiles::BundleHeader m_header;
    BundleFiles::BundleMetaData m_metadata;
};
}

#endif // BUNDLEFILESCHEME_H
