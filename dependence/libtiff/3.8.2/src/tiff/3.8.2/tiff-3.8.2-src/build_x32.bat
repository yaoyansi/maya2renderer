copy nmake_x32.opt nmake.opt

rem nmake /f makefile.vc

%comspec% /k ""D:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x86

rem nmake /f makefile.vc