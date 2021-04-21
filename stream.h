#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <fstream>
#include <iostream>

class Stream
{
public:
    Stream();
private:
    union u {
        std::fstream fstream;
        std::istream istream;
        std::ostream ostream;
        std::iostream iostream;
        std::vector<std::uint8_t> vector;
    };
};

#endif // STREAM_H
