#ifndef NODE_H
#define NODE_H

#include "ibundlereadable.h"

#include <string>

namespace VRCE::BundleFiles {

class Node : public BundleFiles::IBundleReadable
{
public:
    Node() noexcept;

    void read(VRCE::BundleFiles::BundleReader& reader) override;

    std::string_view path() const noexcept;
    std::int64_t offset() const noexcept;
    std::int64_t size() const noexcept;
    std::int32_t blobIndex() const noexcept;
private:
    std::string m_path;
    std::string m_pathOrigin;
    std::int64_t m_offset;
    std::int64_t m_size;
    std::int32_t m_blobIndex;
};

}

#endif // NODE_H
