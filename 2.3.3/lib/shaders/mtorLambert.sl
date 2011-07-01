/* $Revision: #2 $ */
/*-______________________________________________________________________
**
** Copyright (c) 1998 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**                    RESTRICTED RIGHTS NOTICE
**
** Use, duplication, or disclosure by the Government is subject to the
** following restrictions:  For civilian agencies, subparagraphs (a) through
** (d) of the Commercial Computer Software--Restricted Rights clause at
** 52.227-19 of the FAR; and, for units of the Department of Defense, DoD
** Supplement to the FAR, clause 52.227-7013 (c)(1)(ii), Rights in
** Technical Data and Computer Software.
**
** Pixar
** 1001 W Cutting Blvd
** Richmond, CA  94804
**
** ______________________________________________________________________
*/
#include <walias.h>

surface
mtorLambert( 
            float diffuseCoeff = .8;
            color ambientColor = color(0);
            color incandescence = color(0);
            float translucenceCoeff = 0;
            float refractiveIndex = 1; /* unsupported */
            color refractedColor = color(1); /* unsupported */
            float glowIntensity = 0; /* unsupported */
            )
{
    normal Nf;
    vector V;
    color Ia, Id, Itr;
    normal Nn = normalize(N);
    Nf = faceforward( Nn, I, Nn );
    V = -normalize(I);
    Ia = waliasAmbient(Nf, ambientColor);
    Id = diffuseCoeff * diffuse(Nf);
    Itr = waliasTranslucence(Nf, translucenceCoeff);
    Oi = Os;
    Ci = Os * Cs * (Ia + Id + Itr + incandescence);
}
