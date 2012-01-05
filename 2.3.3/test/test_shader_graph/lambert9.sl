void lambert11 (
 output vector outColor;
)
{
 vector inColor = vector ( 0, 0.01374995708, 0.5 );
 vector transparency = vector ( 0, 0, 0 );
 vector ambientColor = vector ( 0, 0, 0 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 vector outTransparency = vector ( 0, 0, 0 );
 extern normal N;
 normal Nn = normalize( N );
 outTransparency = transparency;
 Oi = Os * color ( 1 - outTransparency );
 outColor = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambientColor ) );
 Ci = Cs * Oi * color outColor;
}

void lambert10 (
 vector inColor;
 output vector outColor;
)
{
 vector transparency = vector ( 0, 0, 0 );
 vector ambientColor = vector ( 0, 0, 0 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 vector outTransparency = vector ( 0, 0, 0 );
 extern normal N;
 normal Nn = normalize( N );
 outTransparency = transparency;
 Oi = Os * color ( 1 - outTransparency );
 outColor = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambientColor ) );
 Ci = Cs * Oi * color outColor;
}

void lambert13 (
 output vector outColor;
)
{
 vector inColor = vector ( 0.4796666503, 0.5, 0 );
 vector transparency = vector ( 0, 0, 0 );
 vector ambientColor = vector ( 0, 0, 0 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 vector outTransparency = vector ( 0, 0, 0 );
 extern normal N;
 normal Nn = normalize( N );
 outTransparency = transparency;
 Oi = Os * color ( 1 - outTransparency );
 outColor = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambientColor ) );
 Ci = Cs * Oi * color outColor;
}

void lambert12 (
 vector transparency;
 output vector outColor;
)
{
 vector inColor = vector ( 0.5, 0.5, 0.5 );
 vector ambientColor = vector ( 0, 0, 0 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 vector outTransparency = vector ( 0, 0, 0 );
 extern normal N;
 normal Nn = normalize( N );
 outTransparency = transparency;
 Oi = Os * color ( 1 - outTransparency );
 outColor = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambientColor ) );
 Ci = Cs * Oi * color outColor;
}

void lambert9 (
 vector transparency;
 vector ambientColor;
)
{
 vector inColor = vector ( 0.5, 0.5, 0.5 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 vector outColor = vector ( 0, 0, 0 );
 vector outTransparency = vector ( 0, 0, 0 );
 extern normal N;
 normal Nn = normalize( N );
 outTransparency = transparency;
 Oi = Os * color ( 1 - outTransparency );
 outColor = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambientColor ) );
 Ci = Cs * Oi * color outColor;
}

surface lambert9()
{
 vector lambert11_outColor;
 vector lambert10_outColor;
 vector lambert13_outColor;
 vector lambert12_outColor;

 lambert11(lambert11_outColor);
 lambert10(lambert11_outColor, lambert10_outColor);
 lambert13(lambert13_outColor);
 lambert12(lambert13_outColor, lambert12_outColor);
 lambert9(lambert10_outColor, lambert12_outColor);
}
