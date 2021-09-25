#include <iostream>

#include "endianreader.h"
#include "bundlefilescheme.h"

#include <fstream>
#include <string>

int main()
{
    try {
        auto scheme = VRCE::BundleFileScheme::ReadScheme("avatar.vrca");
    }  catch (std::exception& ex) {
        std::cout << "Exception:" << ex.what() << std::endl;
    }

    return 0;
}
