#include <string>
#include "Note.h"

Note::Note(int tone){
    this->tone = tone;
}

int Note::getTone(){
    return tone;
}

int Note::higherInterval(Note higher){
    int diff { higher.getTone() - tone };
    return diff;
}

int Note::lowerInterval(Note lower){
    int diff { tone - lower.getTone() };
    return diff;
}

std::string Note::name(){
    switch(tone){
        case 0:
            return "A";
            break;
        case 1:
            return "A#";
            break;
        case 2:
            return "B";
            break;
        case 3:
            return "C";
            break;
        case 4:
            return "C#";
            break;
        case 5:
            return "D";
            break;
        case 6:
            return "D#";
            break;
        case 7:
            return "E";
            break;
        case 8:
            return "F";
            break;
        case 9:
            return "F#";
            break;
        case 10:
            return "G";
            break;
        case 11:
            return "G#";
            break;
        // TODO add default
    }
    
    //return "p";
}