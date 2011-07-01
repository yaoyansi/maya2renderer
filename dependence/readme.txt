
- aqsis 在vc下设置preprocessor无效，所以把preprocessor（比如，AQSIS_STATIC_LINK,__LIQUID__）写在\aqsis\1.6.0\build\include\aqsis\config.h里
- 编译libtiff：
  1.先编译jpeg（E:\dev\tools\GnuWin32\src\jpeg\6b\jpeg-6b-src\jpeg.sln或参考http://www.cnblogs.com/yaoyansi/articles/1867346.html）
  2.清理./libtiff\3.8.2\src\tiff\3.8.2\tiff-3.8.2-src\libtiff/目录下的中间文件；
  3.点击./libtiff\3.8.2\src\tiff\3.8.2\tiff-3.8.2-src/build_x32.bat或build_x64.bat，生成新的nmake.opt；
  4.在弹出的cmd窗口里输入nmake /f makefile.vc，（回车），编译后生成./libtiff\3.8.2\src\tiff\3.8.2\tiff-3.8.2-src\libtiff/libtiff.lib
