surface occlude2(float  samples = 32, 
                        maxdist = 100000)
{
normal  n = normalize(N),
        nf = faceforward(n, I);
float   occ = occlusion(P, nf, samples, "maxdist", maxdist);
 
Oi = Os;
Ci = (1 - occ) * Cs * Oi;
}