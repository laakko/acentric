#ifndef MUSIC_READER_H
#define MUSIC_READER_H

# include <string>
# include <vector>
#include "Note.h"

# include "MusicParser.hxx"

class MusicReader : public MusicParserResult
{
public:
    static int parseInt(const std::string&);
    static Note parseNote(const std::string&);

private:
    static MusicParserResult parse(const std::string&);
};

#endif // MUSIC_READER_H
