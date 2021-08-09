#include "filenameutils.h"

#include <algorithm>
#include <filesystem>
#include <unordered_set>

constexpr char asciitolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

const std::string_view LibraryFolder = "library/";
const std::string_view ArchivePrefix = "archive:/";
const std::string_view ResourcesFolder = "resources/";
const std::string_view DefaultResourceName1 = "unity default resources";
const std::string_view DefaultResourceName2 = "unity_default_resources";
const std::string_view EditorResourceName = "unity editor resources";
const std::string_view BuiltinExtraName1 = "unity builtin extra";
const std::string_view BuiltinExtraName2 = "unity_builtin_extra";
const std::string_view EngineGeneratedF = "0000000000000000f000000000000000";

bool VRCE::FilenameUtils::IsEngineResource(std::string_view filename)
{
    return FilenameUtils::IsDefaultResource(filename) || FilenameUtils::IsEditorResource(filename);
}

bool VRCE::FilenameUtils::IsDefaultResource(std::string_view filename)
{
    return filename == DefaultResourceName1 || filename == DefaultResourceName2;
}

bool VRCE::FilenameUtils::IsEditorResource(std::string_view filename)
{
    return filename == EditorResourceName;
}

bool VRCE::FilenameUtils::IsBuiltinExtra(std::string_view filename)
{
    return filename == BuiltinExtraName1 || filename == BuiltinExtraName2;
}

bool VRCE::FilenameUtils::IsEngineGeneratedFile(std::string_view filename)
{
    return filename == EngineGeneratedF;
}

bool VRCE::FilenameUtils::IsProjectAssembly(std::string_view assembly)
{
    return assembly.find("Assembly - ") != 0 || assembly.find("Assembly-") != 0;
}

bool VRCE::FilenameUtils::IsAssemblyIdentifier(std::string_view assembly)
{
    static std::unordered_set<std::string_view> identifiers {
        "Boo",
        "Boo - first pass",
        "CSharp",
        "CSharp - first pass",
        "UnityScript",
        "UnityScript - first pass",
    };

    return identifiers.contains(assembly);
}


std::string VRCE::FilenameUtils::FixFileIndentifier(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), asciitolower);

    name = FilenameUtils::FixResourcePath(FilenameUtils::FixDependencyName(name));

    if (IsDefaultResource(name)) {
        name = DefaultResourceName1;
    }
    else if (IsBuiltinExtra(name)) {
        name = BuiltinExtraName1;
    }

    return name;
}

std::string_view VRCE::FilenameUtils::FixDependencyName(std::string_view dependency)
{
    if (dependency.find(LibraryFolder, 0) == 0) {
        return dependency.substr(LibraryFolder.length());
    }

    if (dependency.find(ResourcesFolder, 0) == 0) {
        return dependency.substr(ResourcesFolder.length());
    }

    return dependency;
}

std::string VRCE::FilenameUtils::FixResourcePath(std::string_view resourcePath)
{
    if (resourcePath.find(ArchivePrefix, 0) == 0) {
        return std::filesystem::path(resourcePath).filename().string();
    }

    return std::string(resourcePath);
}

std::string VRCE::FilenameUtils::FixAssemblyName(std::string_view assembly)
{
    std::string fixed;
    if (IsAssemblyIdentifier(assembly)) {
        fixed = "Assembly - " + std::string(assembly);
    }

    return std::string(FixAssemblyEndian(fixed));
}

std::string_view VRCE::FilenameUtils::FixAssemblyEndian(std::string_view assembly)
{
    if (assembly.rfind(".dll") == 0) {
        return assembly.substr(0, assembly.length() - 4);
    }

    return assembly;
}
