light liquiddistant(
   float intensity = 1;
   color lightcolor = 1;

   string shadowname = "";  /* shadow map name or "raytrace" for traced shadows */
   float shadowbias = 0.01;
   float shadowblur = 0.0;
   float shadowsamples = 16; /* samples or rays */
   uniform float shadowfiltersize = 1;
   color shadowcolor = 0;

   output varying color __shadow = 0;
   output varying color __unshadowed_Cl = 0;
   output float __nondiffuse = 0;  /* set to 1 to exclude from diffuse light */
   output float __nonspecular = 0; /* set to 1 to exclude from highlights */
)
{
  solar( vector "shader" ( 0, 0, 1 ), 0 ) {

    if( shadowname != "" )
      __shadow = shadow( shadowname, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
    else
      __shadow = 0;

    Cl = intensity;
    __unshadowed_Cl = Cl * lightcolor;
#ifdef DELIGHT
    Cl *= mix( lightcolor, shadowcolor, __shadow );
#else
    Cl *= mix( lightcolor, shadowcolor, ( comp( __shadow, 0 ) + comp( __shadow, 1 ) + comp( __shadow, 2 ) ) / 3 );
#endif
  }

}
