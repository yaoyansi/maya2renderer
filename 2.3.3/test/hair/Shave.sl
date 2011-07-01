
/*
Shave and a Haircut emulation shader (c) 2007 Joe Alter, Inc
by Joe Alter
*/

surface Shave (float Ka = 0, SHAVEambdiff = .6, SHAVEspec = .35, SHAVEgloss = .07,SHAVEopacity = 1.0,SHAVEselfshad=1;
color SHAVEspec_color=1,rootcolor=1,tipcolor=1;)
 { 
 vector T = normalize (dPdv); /* tangent along length of hair */
 vector V = -normalize(I); /* V is the view vector */
 float df2 = 0,diffterm=0;
 color Cspec = 0, Cdiff = 0; /* collect specular & diffuse light */
color mixed=1;
 float rawspec;
 color Cl2;
 float  vt;
 float	tl;
/* Looping over lights, per apadoca paper, the math's a bit different */
 illuminance (P) 
   {
	float sq2;
   df2=(T.normalize(L));  
   df2*=df2;
   df2=1.0-df2;
   if (df2<0) df2=0;
	if (df2>0)
   df2=sqrt(df2); 
   diffterm=df2; /* diffuse */
	if (diffterm<0) diffterm=0;



   vt =  V.T ;
	sq2=1.0-vt*vt;
	if (sq2<0) sq2=0;
	if (sq2>0)
	sq2=sqrt(sq2);
   rawspec = df2* sqrt( 1.0- vt * vt ) -  (normalize(L). T ) * vt; /* raw specular */
   if (rawspec<0) rawspec=0; 

   diffterm=(1.0-SHAVEambdiff)+diffterm*SHAVEambdiff; /* limits gamut of diffuse term */

   Cl2=Cl*SHAVEselfshad+(1-SHAVEselfshad); /* limits the gamut of shadowing */
   Cspec += Cl2*pow( rawspec, 1.0 / ( 3.0 * ( .101 - SHAVEgloss ) ) )*.5;   /* specular exponent x illumination */
   Cdiff += Cl2*diffterm; /* diffuse x illumination */
   }
 mixed = mix( rootcolor, tipcolor, v );
 Oi = Os*SHAVEopacity;
  Ci = Oi * Cs * mixed* (Ka*ambient() + Cdiff) + ( Cspec * SHAVEspec_color *SHAVEspec);  /*sum terms and premult color x opac */
 }