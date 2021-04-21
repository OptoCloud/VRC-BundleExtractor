#ifndef BUNDLETYPE_H
#define BUNDLETYPE_H

namespace VRCE::BundleFiles {
struct BundleType
{
    enum Enums : int
    {
        UnityRaw = 0,
        UnityWeb = 1,
        UnityFS  = 2,
    };

    BundleType() : m_value(0) {}
    BundleType(int value) : m_value(value) {}

    inline void setValue(int value) noexcept { m_value = value; }
    inline int value() const noexcept { return m_value; }

    constexpr bool isRawWeb() const noexcept { return m_value == UnityRaw || m_value == UnityWeb; }
private:
    int m_value;
};
}

#endif // BUNDLETYPE_H
