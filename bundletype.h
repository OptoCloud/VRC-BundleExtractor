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

    constexpr BundleType() noexcept : m_value(0) {}
    constexpr BundleType(int value) noexcept : m_value(value) {}

    constexpr void setValue(int value) noexcept { m_value = value; }
    constexpr int value() const noexcept { return m_value; }

    constexpr bool isRawWeb() const noexcept { return m_value == UnityRaw || m_value == UnityWeb; }

    constexpr bool operator==(BundleType other) const noexcept {
        return m_value == other.m_value;
    }
    constexpr bool operator!=(BundleType other) const noexcept {
        return m_value != other.m_value;
    }
    constexpr bool operator==(BundleType::Enums other) const noexcept {
        return m_value == other;
    }
    constexpr bool operator!=(BundleType::Enums other) const noexcept {
        return m_value != other;
    }
private:
    int m_value;
};
}

#endif // BUNDLETYPE_H
