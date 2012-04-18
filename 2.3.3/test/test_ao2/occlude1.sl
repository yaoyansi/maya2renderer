surface occlude1(float  samples = 32)
{
normal  n = normalize(N),
        nf = faceforward(n, I);
float   hits = 0;
 
gather("illuminance", P, nf, PI/2, samples, "distribution","cosine")
    {
    hits += 1;
    }
/* find the average occlusion factor */
float average = hits / samples;
  
Ci = (1 - average) * Cs;
Oi = 1;
}