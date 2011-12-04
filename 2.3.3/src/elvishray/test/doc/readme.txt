This is a test program which aims to render the elvishrender api script(e.g. script.er) into an image.

Steps:
- In VC project property, set "Work directory" and "Aditional Library Directories" to the right directory,
  e.g. if you use elvishrender r990, the values are:
    Work directory                =$(ElvishrenderRoot)\build\r990\x86
    Aditional Library Directories =$(ElvishrenderRoot)\build\r990\x86\lib
    
- open elvishrender_test.cpp and set your script file in test_liquid2er(), 
  e.g.
	void test_liquid2er()
	{ 
		#include"script.er"//<----- use your own elvishender api script file here.
	}
- build, and run.
That's all.