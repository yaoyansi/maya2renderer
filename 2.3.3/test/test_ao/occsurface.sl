#include <normals.h>

    surface 
    occsurf2(float samples = 64, maxvariation = 0.02)
    {
      normal Ns = shadingnormal(N); // normalize N and flip it if backfacing

      // Compute occlusion
      float occ = occlusion(P, Ns, samples, "maxvariation", maxvariation);

      // Set Ci and Oi
      Ci = (1 - occ) * Cs * Os;
      Oi = Os;
    }
