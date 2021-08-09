#include "bundleheader.h"

#include "bundlereader.h"

VRCE::BundleFiles::BundleType VRCE::BundleFiles::BundleHeader::ParseSignature(const std::string &signature)
{
    if (signature == "UnityRaw") {
        return BundleType::UnityRaw;
    }
    else if (signature == "UnityWeb") {
        return BundleType::UnityWeb;
    }
    else if (signature == "UnityFS") {
        return BundleType::UnityFS;
    }

    throw std::invalid_argument("Unsupported signature " + signature);
}

bool VRCE::BundleFiles::BundleHeader::TryParseSignature(const std::string &signature, VRCE::BundleFiles::BundleType &type)
{
    try {
        type = ParseSignature(signature);
        return true;
    }  catch (...) {
        return false;
    }
}

bool VRCE::BundleFiles::BundleHeader::IsBundleHeader(VRCE::BinaryReader& reader)
{
    auto stream = reader.readSource();

    //auto position = stream.tellg();

    std::string signature = reader.readString();

    //stream.seekg(position, stream.beg);

    BundleType type;
    return TryParseSignature(signature, type);
}

VRCE::BundleFiles::BundleHeader::BundleHeader()
    : m_signature()
    , m_version()
    , m_unityWebBundleVersion()
    , m_unityWebMinimumRevision()
    , m_rawWeb(nullptr)
    , m_fileStream(nullptr)
{
}

VRCE::BundleFiles::BundleHeader::BundleHeader(const VRCE::BundleFiles::BundleHeader& other)
    : m_signature(other.m_signature)
    , m_version(other.m_version)
    , m_unityWebBundleVersion(other.m_unityWebBundleVersion)
    , m_unityWebMinimumRevision(other.m_unityWebMinimumRevision)
    , m_rawWeb(other.m_rawWeb)
    , m_fileStream(other.m_fileStream)
{
}

void VRCE::BundleFiles::BundleHeader::read(VRCE::BundleFiles::BundleReader& reader)
{
    std::string signature = reader.readString();
    m_signature = ParseSignature(signature);

    m_version = (BundleVersion)reader.read32s();

    m_unityWebBundleVersion = reader.readString();

    auto engineVersion = reader.readString();
    m_unityWebMinimumRevision = VRCE::Version::Parse(engineVersion);

    switch (m_signature.value()) {
    case BundleType::UnityRaw:
    case BundleType::UnityWeb:
        m_rawWeb = std::make_shared<VRCE::BundleFiles::BundleRawWebHeader>();
        m_rawWeb->read(reader, m_version);
        break;
    case BundleType::UnityFS:
        m_fileStream = std::make_shared<VRCE::BundleFiles::BundleFileStreamHeader>();
        m_fileStream->read(reader);
        break;
    default:
        throw "Unkown bundle signature " + signature;
    }
}

VRCE::BundleFiles::BundleType VRCE::BundleFiles::BundleHeader::signature() const
{
    return m_signature;
}

VRCE::BundleFiles::BundleVersion VRCE::BundleFiles::BundleHeader::version() const
{
    return m_version;
}

VRCE::BundleFiles::BundleFlags VRCE::BundleFiles::BundleHeader::flags() const
{
    if (m_signature == BundleType::UnityFS) {
        return m_fileStream->flags();
    }
    return 0;
}

std::shared_ptr<VRCE::BundleFiles::BundleRawWebHeader> VRCE::BundleFiles::BundleHeader::rawWeb()
{
    return m_rawWeb;
}

std::shared_ptr<VRCE::BundleFiles::BundleFileStreamHeader> VRCE::BundleFiles::BundleHeader::fileStream()
{
    return m_fileStream;
}

VRCE::BundleFiles::BundleHeader &VRCE::BundleFiles::BundleHeader::operator=(const VRCE::BundleFiles::BundleHeader& other)
{
    m_signature = other.m_signature;
    m_unityWebBundleVersion = other.m_unityWebBundleVersion;
    m_unityWebMinimumRevision = other.m_unityWebMinimumRevision;
    m_rawWeb = other.m_rawWeb;
    m_fileStream = other.m_fileStream;

    return *this;
}
