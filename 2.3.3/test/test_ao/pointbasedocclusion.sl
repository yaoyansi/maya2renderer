//#include "normals.h"
#include <normals.h>
//#include <lib/shaders/normals.h>
//#include <${RMANTREE}/lib/shaders/normals.h>
//#include <"D:/Program Files/Pixar/RenderManProServer-13.5.2/lib/shaders/normals.h">

surface 
pointbasedocclusion (string filename = "";
	   	         string hitsides = "front";
                         float maxdist = 1e15, falloff = 0, falloffmode = 0,
                         samplebase = 0,
		         clampocclusion = 0, maxsolidangle = 0.05; ) 
    {
      normal Ns = shadingnormal(N);        
      float occ;

      occ = occlusion(P, Ns, 0, "pointbased", 1, "filename", filename,
                      "hitsides", hitsides,
                      "maxdist", maxdist, "falloff", falloff,
                      "falloffmode", falloffmode,
                      "samplebase", samplebase, "clamp", clampocclusion,
                      "maxsolidangle", maxsolidangle);

      Ci = (1 - occ) * Os;
      Oi = Os;
    }
