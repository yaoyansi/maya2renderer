light liquidpoint(
    uniform float  intensity     = 1;
    uniform color  lightcolor    = 1;
    uniform float decay          = 0;

    uniform string shadownamepx  = "";
    uniform string shadownamenx  = "";
    uniform string shadownamepy  = "";
    uniform string shadownameny  = "";
    uniform string shadownamepz  = "";
    uniform string shadownamenz  = "";

    uniform float  shadowbias    = 0.01;
    uniform float  shadowblur    = 0.01;
    uniform float  shadowsamples = 16;
    uniform float  shadowfiltersize = 1;
    uniform color  shadowcolor   = 0;

    output varying color __shadow = 0;
    output varying color __unshadowed_Cl = 0;
    output float __nondiffuse    = 0;
    output float __nonspecular   = 0;
)
{
  illuminate( point "shader" ( 0, 0, 0 ) ) {

    vector Lworld = vtransform( "world", L );

    float Lx = xcomp( Lworld );
    float LxAbs = abs( Lx );
    float Ly = ycomp( Lworld );
    float LyAbs = abs( Ly );
    float Lz = zcomp( Lworld );
    float LzAbs = abs( Lz );

    if( ( LxAbs > LyAbs ) && ( LxAbs > LzAbs ) ) {
      if( ( Lx > 0 ) && ( shadownamepx != "" ) )
        __shadow = shadow( shadownamepx, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
      else if( shadownamenx != "")
        __shadow = shadow( shadownamenx, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
    } else if( (LyAbs > LxAbs) && ( LyAbs > LzAbs ) ) {
      if( ( Ly > 0 ) && ( shadownamepy != "" ) )
        __shadow = shadow( shadownamepy, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
      else if( shadownameny != "" )
        __shadow = shadow( shadownameny, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
    } else if( ( LzAbs > LyAbs ) && ( LzAbs > LxAbs ) ) {
      if( ( Lz > 0 ) && ( shadownamepz != "" ) )
        __shadow = shadow( shadownamepz, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
      else if( shadownamenz != "")
        __shadow = shadow( shadownamenz, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
    } else
      __shadow = 0;

    Cl = intensity * pow( 1 / zcomp( L ), decay );
    __unshadowed_Cl = Cl * lightcolor;
#ifdef DELIGHT
    Cl *= mix( lightcolor, shadowcolor, __shadow );
#else
    Cl *= mix( lightcolor, shadowcolor, ( comp( __shadow, 0 ) + comp( __shadow, 1 ) + comp( __shadow, 2 ) ) / 3 );
#endif
  }
}
