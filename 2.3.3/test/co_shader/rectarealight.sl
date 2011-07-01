//
// rectarealight.sl - Simple area light source shader.
// An example of the new shader object system in PRMan 13.5.
// Per Christensen, 2007.
//
// Generate (unstratified) illumination directions on rectangular  area light
// source
//

class
rectarealight(
       float intensity = 1;
       color lightcolor = 1;
       uniform float samples = 16;
       point center = point "shader" (0,0,0); // center of rectangle
       vector udir = vector "shader" (1,0,0); // axis of rectangle
       vector vdir = vector "shader" (0,1,0)) // axis of rectangle
{
    public void light( output vector L;         // unused
                       output color Cl;         // unused
                       point P = (0,0,0);
                       output color lightcolors[] = { };
                       output vector lightdirs[] = { } )
    {
       vector rnd;
       point samplepos;
       float rnd1, rnd2;
       uniform float s;

       resize(lightcolors, samples);   // note use of resizable arrays
       resize(lightdirs, samples);

       for (s = 0; s < samples; s += 1) {
           rnd1 = 2 * random() - 1;
           rnd2 = 2 * random() - 1;
           samplepos = center + rnd1 * udir + rnd2 * vdir;
           lightdirs[s] = samplepos - P;
           lightcolors[s] = intensity * lightcolor / samples;
       }

       // Clear L and Cl, even though they're unused.
       L = (0,0,0);
       Cl = (0,0,0);
    }
}
