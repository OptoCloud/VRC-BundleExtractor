#ifndef BUNDLEHEADER_H
#define BUNDLEHEADER_H

#include "bundletype.h"
#include "bundleversion.h"
#include "endianreader.h"
#include "version.h"
#include "bundlefilestreamheader.h"
#include "bundlerawwebheader.h"

#include <string>
#include <exception>

namespace VRCE::BundleFiles {
class BundleHeader
{
public:
    static inline BundleType ParseSignature(const std::string& signature);
    static bool TryParseSignature(const std::string& signature, BundleType& type);
    static bool IsBundleHeader(BinaryReader& reader);

    BundleHeader();
    BundleHeader(const BundleHeader& other);

    void read(VRCE::BundleFiles::BundleReader& reader);

    BundleFiles::BundleType signature() const;
    BundleFiles::BundleVersion version() const;
    BundleFiles::BundleFlags flags() const;

    std::shared_ptr<BundleRawWebHeader> rawWeb();
    std::shared_ptr<BundleFileStreamHeader> fileStream();

    BundleHeader& operator=(const BundleHeader& other);
private:
    BundleFiles::BundleType m_signature;
    BundleFiles::BundleVersion m_version;
    std::string m_unityWebBundleVersion;
    Version m_unityWebMinimumRevision;
    std::shared_ptr<BundleRawWebHeader> m_rawWeb;
    std::shared_ptr<BundleFileStreamHeader> m_fileStream;
};
}

#endif // BUNDLEHEADER_H
