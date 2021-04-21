#ifndef FILESCHEME_H
#define FILESCHEME_H

#include "fileentrytype.h"
#include "fileidentifier.h"

#include <filesystem>

namespace VRCE {
class FileScheme
{
public:
    FileScheme(std::filesystem::path filePath);
private:
    std::filesystem::path m_filePath;
    FileEntryType m_schemeType;
    std::vector<SerializedFiles::FileIdentifier> m_dependencies;
};
}

#endif // FILESCHEME_H
