void blinn6 (
 output vector outColor;
)
{
 vector inColor = vector ( 0.5, 0.5, 0.5 );
 vector transparency = vector ( 0, 0, 0 );
 vector ambColor = vector ( 0, 0, 0 );
 vector incandescence = vector ( 0, 0, 0 );
 float diffusion = float 0.8000000119;
 float eccentricity = float 0.3000000119;
 float specRollOff = float 0.6999999881;
 vector specColor = vector ( 0.5, 0.5, 0.5 );
 extern normal N;
 normal Nn = normalize( N );
 Oi = Os * color ( 1 - transparency );
 vector Cdiffuse;
 Cdiffuse = incandescence +
            ( inColor * ( diffusion * 
                          vector diffuse( Nn ) +
                          ambColor ) );
 vector Cspecular = 0;
 float eccSq = pow( eccentricity, 2 );
 vector V = normalize( -I );
 float NV = Nn . V;
 illuminance( P, Nn, PI / 2 )
 {
  vector Ln = normalize( L );
  vector H = normalize( V + Ln );
  float NH = Nn . H;
  float NL = Nn . Ln;
  float VH = V . H;
  float D = pow( eccSq / 
                 ( pow( NH, 2 ) * 
                   ( eccSq - 1 ) + 1 ), 2 );
  float G = min( min( 1, 2 * NH * NV / VH ), 
                 2 * NH * NL / VH );
  Cspecular += ( vector Cl * ( D * G / NV ) );
 }
 Cspecular *= specColor;
 Cspecular *= mix( 1, specRollOff, );
 outColor = Cdiffuse + Cspecular;
 Ci = Cs * Oi * color outColor;
}

void lambert8 (
 output vector outColor;
)
{
 vector inColor = vector ( 0.5, 0.5, 0.5 );
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

void lambert7 (
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

surface lambert7()
{
 vector blinn6_outColor;
 vector lambert8_outColor;

 blinn6(blinn6_outColor);
 lambert8(lambert8_outColor);
 lambert7(blinn6_outColor, lambert8_outColor);
}
