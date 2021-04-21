#ifndef VECSTREAMBUF_H
#define VECSTREAMBUF_H

#include <string>
#include <streambuf>
#include <vector>

template<typename CharT, typename TraitsT = std::char_traits<CharT>>
class VecStreamBuf : public std::basic_streambuf<CharT, TraitsT>
{
public:
    VecStreamBuf(std::vector<CharT> &vec) {
        std::basic_streambuf<CharT, TraitsT>::setg(vec.data(), vec.data(), vec.data() + vec.size());
    }
};

#endif // VECSTREAMBUF_H
