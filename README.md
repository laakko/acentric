![Acentric Logo](/acentric_logo.png)

## This is a fork of the original project: https://github.com/r734/acentric

## Acentric: a work-in-progress music theory library and language
From the original readme: 
*"This is a work-in-progress library for music theory analysis. Its purpose is to assist students, musicians, and researchers with calculating and understanding complex music theory concepts and automating tedious tasks such as determining scale degrees or analyzing musical parts for compliance with counterpoint rules.*

*The library will serve as a (hopefully) efficient, well-documented *back-end for other programs/interfaces*."*

### Compile and run
Go to the root directory of the project, open a command window or terminal and type:

```sh
g++ -std=c++11 main.cpp Note.cpp Interval.cpp Chord.cpp Scale.cpp -o main                                
./main
```

### Scope/Work in Progress
Priority of concepts to be implemented by this library include:

* More Scales
* Harmony/dissonance calculation for simultaneous notes/chords
