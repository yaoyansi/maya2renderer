copy nmake_x64.opt nmake.opt

rem nmake /f makefile.vc

%comspec% /k ""D:\Program Files (x86)\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x64

rem nmake /f makefile.vc