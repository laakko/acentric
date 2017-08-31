#include <iostream>     // cin/cerr etc ...
#include <string>       // getline

#include "MusicReader.h"

int main (int argc, char *argv[])
{
    //auto result = MusicReader::readNote("C###4;");
    //std::cout << result << std::endl;
    MusicReader::ReadMusicInteractive();
}