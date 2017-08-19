#include <iostream>     // cin/cerr etc ...
#include <string>       // getline

#include "MusicReader.h"

int main (int argc, char *argv[])
{
    auto result = MusicReader::parseInt("1234");
    std::cout << result << std::endl;
}