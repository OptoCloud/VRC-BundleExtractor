#ifndef FILESCHEMELIST_H
#define FILESCHEMELIST_H

#include "filescheme.h"

#include <filesystem>

namespace VRCE {
class FileSchemeList : public FileScheme
{
public:
    FileSchemeList(std::filesystem::path filePath);
};
}

#endif // FILESCHEMELIST_H
