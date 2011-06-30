Note for compiling with MSVC++6

You'll need to modify the standard header basetsd.h in the MSVC include dir as follow:

line 124 <BASETSD.H>:
original:
  typedef unsigned long UINT_PTR, *PUINT_PTR;
modified:
  typedef unsigned UINT_PTR, *PUINT_PTR;
  
