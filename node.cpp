#include "node.h"

#include "bundlereader.h"
#include "filenameutils.h"

constexpr bool HasBlobIndex(VRCE::BundleFiles::BundleType signature)
{
    return signature == VRCE::BundleFiles::BundleType::UnityFS;
}

VRCE::BundleFiles::Node::Node() noexcept
    : m_path()
    , m_pathOrigin()
    , m_offset()
    , m_size()
    , m_blobIndex()
{
}

void VRCE::BundleFiles::Node::read(VRCE::BundleFiles::BundleReader& reader)
{
    if (HasBlobIndex(reader.signature())) {
        m_offset = reader.read64s();
        m_size = reader.read64s();
        m_blobIndex = reader.read32s();
        m_pathOrigin = reader.readString();
    }
    else {
        m_pathOrigin = reader.readString();
        m_offset = reader.read32s();
        m_size = reader.read32s();
    }
    m_path = FilenameUtils::FixFileIndentifier(m_pathOrigin);
}

std::string_view VRCE::BundleFiles::Node::ToString()
{
    return m_path;
}
