#ifndef FILENAMEUTILS_H
#define FILENAMEUTILS_H

#include <string>
#include <string_view>

namespace VRCE::FilenameUtils {
bool IsEngineResource(std::string_view filename);
bool IsDefaultResource(std::string_view filename);
bool IsEditorResource(std::string_view filename);
bool IsBuiltinExtra(std::string_view filename);
bool IsEngineGeneratedFile(std::string_view filename);
bool IsProjectAssembly(std::string_view assembly);
bool IsAssemblyIdentifier(std::string_view assembly);
std::string FixFileIndentifier(std::string name);
std::string_view FixDependencyName(std::string_view dependency);
std::string FixResourcePath(std::string_view resourcePath);
std::string FixAssemblyName(std::string_view assembly);
std::string_view FixAssemblyEndian(std::string_view assembly);
}

#endif // FILENAMEUTILS_H
