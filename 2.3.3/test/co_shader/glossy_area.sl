//
//
// A surface with Ward isotropic glossy reflection, illuminated
// by area light sources.
// An example of the new shader object system in PRMan 13.5.
// Per Christensen, 2007.
//

#include "normals.h"
#include "wardglossy.h"

//
// Surface shader class definition
//

class glossy_area(string texturename = "";
                  float Kd = 0.5, Kg = 0.5;
                  float alpha_u = 0.05;
                  float RRthreshold = 0.01;
)
{
    // Ward isotropic glossy BRDF
    public void surface(output color Ci, Oi) {
        color refl, sumrefl = 0;
        color trans;
        normal Ns = shadingnormal(N);
        vector In = normalize(I);
        vector lightDir;
        color tex = 1;
        float dot_i, maxrefl;
        uniform float s;

        shader lights[] = getlights();
        uniform float i, nlights = arraylength(lights);

        // Texture
        if (texturename != "")
            tex = texture(texturename);

        // For each light source ...
        for (i = 0; i < nlights; i += 1) {

            // Get lightcolors, lightdirs from light.
            vector L;                   // unused, but required argument
            color Cl;                   // also unused.
            color lightcolors[];        // note use of resizable arrays
            vector lightdirs[];
            lights[i]->light(L, Cl,
                             "P", P,
                             "lightcolors", lightcolors,
                             "lightdirs", lightdirs);
            uniform float nsamples = arraylength(lightcolors);

            // Evaluate glossy (and diffuse) BRDF for the light
            // directions
            color reflcoeffs[nsamples];
            evaluateWardGlossy(P, Ns, In,
                               Kd * tex * Cs, color(Kg), alpha_u,
                               nsamples, lightdirs, reflcoeffs);

            // Accumulate illumination; shoot shadow rays only where
            // they matter
            for (s = 0; s < nsamples; s += 1) {

                // Compute cosine term
                lightDir = normalize(lightdirs[s]);
                dot_i = lightDir . Ns;

                // Reflected light is the product of incident
                // illumination, a cosine term, and the BRDF
                refl = lightcolors[s] * dot_i * reflcoeffs[s];

                // Compute shadow -- but only if the potentially
                // reflected light is bright enough to matter.  This
                // is sometimes an important optimization!  For
                // example, no shadow rays need to be traced at points
                // with a black texture and no glossy highlight or if
                // the light source is dark-ish.  The point is that we
                // need information both from the surface and the
                // light source to determine whether shadow rays need
                // to be traced.
                maxrefl = max(refl[0], refl[1], refl[2]);
                if (maxrefl > RRthreshold)
                    trans = transmission(P, P + lightdirs[s]);
                else if (maxrefl > RRthreshold * random())
                    // Russian roulette
                    trans = transmission(P, P + lightdirs[s]);
                else
                    trans = 1; // don't bother tracing shadow rays

                sumrefl += trans * refl;
            }
        }

        // Set Ci and Oi
        Ci = sumrefl * Os;
        Oi = Os;
    }
}
