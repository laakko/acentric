### music-theory (working name)

This is a work-in-progress library for music theory analysis. Its purpose is to assist students, musicians, and researchers with calculating and understanding complex music theory concepts and automating tedious tasks such as determining scale degrees or analyzing musical parts for compliance with counterpoint rules.

The library will serve as a (hopefully) efficient, well-documented *back-end for other programs/interfaces*.

#### Build
This library uses the CMake build system. You need CMake installed on your computer to build the project.

From the root directory, open a command window or terminal and type:

```sh
mkdir build
cd build
cmake ..
```

If you are on Windows using Visual Studio, there will be a .sln file in the `build` folder which can be opened in Visual Studio.

If you are on Linux, there will be a `makefile` in the `build` folder. From `build`, type `make` to build the project.

#### Documentation
Documentation is included in the form of comments in header files and throughout the code. Optionally, you may use Doxygen to generate HTML- or LaTeX documentation based on these comments. Install Doxygen on your system, and from the `build` folder, execute `doxygen Doxyfile`. This will create folders of documentation in your `build` folder.

#### Scope/Work in Progress
Priority of concepts to be implemented by this library include:

* Notes
* Intervals
* Chords
* Scales
* Melodies
* Polyphony (counterpoint) with analysis/rule-checking

Features not currently prioritized (i.e. nice to have but won't happen soon without help) include:

* Input/output, e.g. MIDI file or instrument integration
* Basic user interface - command-line or graphical

#### Level of Detail
The library attempts to support exotic note/interval configurations. For instance, `A####4` is considered a valid note which is enharmonic with C#4. Exotic intervals are similarly supported, with e.g. a doubly-augmented fifth represented by the notation `(A+2)5`.

Because most users will never need such complexity, simple notation is also supported; e.g. `C#` is assumed to be in the fourth octave, and `M3` and `m3` are simply major third and minor third intervals, respectively.

#### Support
This library is being developed in one person's spare time in hopes of helping musically-inclined people anywhere and everywhere. Suggestions and questions submitted by the issue tracker are *completely welcome*, but a quick response (let alone a quick fix/implementation) is not guaranteed!