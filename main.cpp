#include <iostream>

#include "endianreader.h"
#include "bundlefilescheme.h"

#include <fstream>
#include <string>

int main()
{
    auto scheme = VRCE::BundleFileScheme::ReadScheme("avatar.vrca");

    return 0;
}
