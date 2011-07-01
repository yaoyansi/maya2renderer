//
// wardglossy.h
//
// Evaluate Ward's isotropic glossy BRDF for the given light directions
//
void
evaluateWardGlossy( vector P, Nn, In;
                    color Cd, Cg;
                    float alpha;
                    uniform float samples;
                    vector lightdirs[];
                    output color reflcoeffs[] )
{
    vector lightDir, reflDir, h;
    float alpha2, dot_i, dot_r;
    float delta, e, c;
    uniform float s;

    alpha2 = alpha*alpha;
    reflDir = -In; // direction toward eye
    dot_r = reflDir . Nn;

    for (s = 0; s < samples; s += 1) {
        lightDir = normalize(lightdirs[s]);
        dot_i = lightDir . Nn;
        if (dot_i <= 0 || dot_r <= 0) {
            reflcoeffs[s] = 0;
        } else {
            reflcoeffs[s] = Cd; // diffuse comp
            // (cosine term is elsewhere)
            h = normalize(reflDir + lightDir);
            delta = acos(h . Nn);
            e = tan(delta) / alpha;
            c = 1 / sqrt(dot_i * dot_r);
            reflcoeffs[s] +=  //  glossy comp
                Cg * c * exp(-e*e) / (4 * PI * alpha2);
        }
    }
}
