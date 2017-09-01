#ifndef MUSIC_READER_H
#define MUSIC_READER_H

# include <string>
# include <vector>
#include "Note.h"

#include "Parser.hxx"

class MusicReader : public MusicParserResult
{
public:
    static void ReadMusicInteractive(bool debug = false);

    static Note readNote(const std::string&);

private:
    static MusicParserResult parse(const std::string&);
};

#endif // MUSIC_READER_H
