Note for compiling with MSVC2005

1st note: Projects comes with a generic RIB library to avoid linking problem.

2nd note: if you want to compile the generic RIB library, you'll need to create an empty unistd.h
in your MSVC standard include directory (due to the bison/flex file generator), and install zlib headers and libs.

3rd note: to load liquid on x64, zlibwapi.dll needs to be in one of the lib paths, the file is here: liquid\bin\win64lib
