#ifndef MUSIC_READER_H
#define MUSIC_READER_H

# include <string>
# include <vector>

# include "MusicParser.hxx"

class MusicReader : public MusicParserResult
{
public:
    static int parseInt(const std::string&);

private:

};

#endif // MUSIC_READER_H
