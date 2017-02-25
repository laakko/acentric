// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note{

private:
    int tone{ 0 }; // 0 = a, 1 = Bb, etc.

public:
    Note(int tone);
    int getTone();
    int higherInterval(Note);
    int lowerInterval(Note);
    std::string name();
};

#endif // NOTE_H