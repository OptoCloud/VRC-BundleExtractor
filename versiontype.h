#ifndef VERSIONTYPE_H
#define VERSIONTYPE_H

#include <string>

namespace VRCE {
enum class VersionType : std::uint8_t
{
    Alpha = 0,
    Beta,
    Final,
    Patch,

    MaxValue = Patch,
};
namespace VersionTypeExtentions {
constexpr char ToLiteral(VersionType type)
{
    switch (type) {
    case VersionType::Alpha:
        return 'a';
    case VersionType::Beta:
        return 'b';
    case VersionType::Final:
        return 'f';
    case VersionType::Patch:
        return 'p';
    default:
        throw "Unsupported vertion type " + std::to_string((int)type);
    }
}
}
}

#endif // VERSIONTYPE_H
