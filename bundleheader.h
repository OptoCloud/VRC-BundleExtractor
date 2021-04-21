#ifndef BUNDLEHEADER_H
#define BUNDLEHEADER_H

#include "bundletype.h"
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
    static bool IsBundleHeader(IBinaryReader& reader);

    BundleHeader();
    BundleHeader(const BundleHeader& other);

    void read(IBinaryReader& reader);

    BundleType signature() const;

    std::shared_ptr<BundleRawWebHeader> rawWeb();
    std::shared_ptr<BundleFileStreamHeader> fileStream();

    BundleHeader& operator=(const BundleHeader& other);
private:
    BundleType m_signature;
    BundleVersion m_version;
    std::string m_unityWebBundleVersion;
    Version m_unityWebMinimumRevision;
    BundleFlags m_flags;
    std::shared_ptr<BundleRawWebHeader> m_rawWeb;
    std::shared_ptr<BundleFileStreamHeader> m_fileStream;
};
}

#endif // BUNDLEHEADER_H
