
/* Superellipse soft clipping -- straight from uberlight
 * Input:
 *   - point Q on the x-y plane
 *   - the equations of two superellipses (with major/minor axes given by
 *        a,b and A,B for the inner and outer ellipses, respectively)
 * Return value:
 *   - 0 if Q was inside the inner ellipse
 *   - 1 if Q was outside the outer ellipse
 *   - smoothly varying from 0 to 1 in between
 */
float
clipSuperellipse( point Q; /* Test point on the x-y plane */
    float a, b;           /* Inner superellipse */
    float A, B;           /* Outer superellipse */
    float roundness;      /* Same roundness for both ellipses */
  )
{
  float result = 0;
  float x = abs(xcomp(Q)), y = abs(ycomp(Q));
  if (x != 0 || y != 0) {  /* avoid degenerate case */
    if (roundness < 1.0e-6) {
      /* Simpler case of a square */
      result = 1 - (1-smoothstep(a,A,x)) * (1-smoothstep(b,B,y));
    } else if (roundness > 0.9999) {
      /* Simple case of a circle */
      float sqr (float x) { return x*x; }
      float q = a * b / sqrt (sqr(b*x) + sqr(a*y));
      float r = A * B / sqrt (sqr(B*x) + sqr(A*y));
      result = smoothstep (q, r, 1);
    } else {
      /* Harder, rounded corner case */
      float re = 2/roundness;   /* roundness exponent */
      float q = a * b * pow (pow(b*x, re) + pow(a*y, re), -1/re);
      float r = A * B * pow (pow(B*x, re) + pow(A*y, re), -1/re);
      result = smoothstep (q, r, 1);
    }
  }
  return result;
}



light liquidspot(
    uniform float intensity      = 1;
    uniform color lightcolor     = 1;
    uniform float coneangle      = radians( 40 );
    uniform float penumbraangle  = radians( 0 );
    uniform float dropoff        = 0;
    uniform float decay          = 0;

    uniform float barndoors      = 0;
    uniform float leftbarndoor   = 10;
    uniform float rightbarndoor  = 10;
    uniform float topbarndoor    = 10;
    uniform float bottombarndoor = 10;

    uniform string shadowname    = "";
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
  float atten;
  uniform float cosoutside, cosinside, angle;

  uniform vector xaxis = vector "shader"( 1, 0, 0 );
  uniform vector yaxis = vector "shader"( 0, 1, 0 );

  if( penumbraangle < 0 ) {
    angle = coneangle;
    cosoutside = cos( coneangle );
    cosinside = cos( coneangle + penumbraangle );
    //printf("o: %f, i: %f \n", cosoutside, cosinside );
  } else {
    angle = coneangle + penumbraangle;
    cosoutside = cos( angle );
    cosinside = cos( coneangle );
    //printf("o: %f, i: %f \n", cosoutside, cosinside );
  }

  illuminate( point "shader"( 0, 0, 0 ), vector "shader"( 0, 0, 1 ), angle ) {

    float distance = length( L );
    float cosangle2 = L . vector "shader" ( 0, 0, 1 );
    float cosangle = cosangle2 / distance;

    atten = 1 / pow( distance, decay );
    atten *= pow( cosangle, dropoff );
    atten *= smoothstep( cosoutside, cosinside, cosangle );

    if( barndoors != 0 ) {
      float anglex = atan( L . xaxis, cosangle2 );
      float angley = atan( L . yaxis, cosangle2 );

      atten *= smoothstep( min( -bottombarndoor, -bottombarndoor - penumbraangle ),
                           max( -bottombarndoor, -bottombarndoor - penumbraangle), anglex ) *
               ( 1 - smoothstep( min( topbarndoor, topbarndoor + penumbraangle ),
                                 max(topbarndoor, topbarndoor + penumbraangle ), anglex ) );
      atten *= smoothstep( min( -rightbarndoor, -rightbarndoor - penumbraangle ),
                           max( -rightbarndoor, -rightbarndoor - penumbraangle ), angley ) *
               ( 1 - smoothstep( min( leftbarndoor, leftbarndoor + penumbraangle ),
                                 max( leftbarndoor, leftbarndoor + penumbraangle), angley ) );
    }

    if( shadowname != "" )
      __shadow = shadow( shadowname, Ps, "samples", shadowsamples, "blur", shadowblur, "bias", shadowbias, "width", shadowfiltersize );
    else
      __shadow = 0;

    Cl = intensity * atten;
    __unshadowed_Cl = Cl * lightcolor;
#ifdef DELIGHT
    Cl *= mix( lightcolor, shadowcolor, __shadow );
#else
    Cl *= mix( lightcolor, shadowcolor, ( comp( __shadow, 0 ) + comp( __shadow, 1 ) + comp( __shadow, 2 ) ) / 3 );
#endif
  }
}
