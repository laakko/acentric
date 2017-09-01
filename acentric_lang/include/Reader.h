#ifndef MUSIC_READER_H
#define MUSIC_READER_H

# include <string>
# include <vector>
#include "Note.h"

#include "Parser.hxx"

class MusicReader : public ParserResult
{
public:
    static void ReadMusicInteractive(bool debug = false);

    static Note readNote(const std::string&);

private:
    static ParserResult parse(const std::string&);
};

#endif // MUSIC_READER_H
