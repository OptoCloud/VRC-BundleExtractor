#include "bundlescene.h"

#include "endianreader.h"

void VRCE::BundleFiles::BundleScene::read(VRCE::IBinaryReader& reader)
{
    m_compressedSize = reader.read32u();
    m_decompressedSize = reader.read32u();
}

std::uint32_t VRCE::BundleFiles::BundleScene::compressedSize() const
{
    return m_compressedSize;
}

std::uint32_t VRCE::BundleFiles::BundleScene::decompressedSize() const
{
    return m_decompressedSize;
}

std::string VRCE::BundleFiles::BundleScene::toString() const
{
    return "";
}
