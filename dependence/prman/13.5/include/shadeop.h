/* $Revision: #1 $  (Pixar - RenderMan Division)  $Date: 2007/07/06 $ */
/*
** Copyright (c) 1999 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**                      RESTRICTED RIGHTS NOTICE
**
** Use, duplication, or disclosure by the Government is subject to the
** following restrictions:  For civilian agencies, subparagraphs (a) through
** (d) of the Commercial Computer Software--Restricted Rights clause at
** 52.227-19 of the FAR; and, for units of the Department of Defense, DoD
** Supplement to the FAR, clause 52.227-7013 (c)(1)(ii), Rights in
** Technical Data and Computer Software.
**
** Pixar
** 1001 West Cutting Blvd.
** Richmond, CA  94804
*/

#ifndef SHADEOP_H
#define SHADEOP_H

#ifndef DLLEXPORT
#if defined(_WIN32) || defined(_WINDOWS)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#endif /* ifndef DLLEXPORT */

/* Prototype for DSO shadeop "implementation method" */
#define SHADEOP(name) DLLEXPORT int name (void *initdata, int argc, void *argv[])

/* Prototype for DSO shadeop "initialization routine" */
#define SHADEOP_INIT(name) DLLEXPORT void * name (int ctx, void *texturectx)

/* Prototype for DSO shadeop "cleanup routine" */
#define SHADEOP_CLEANUP(name) DLLEXPORT void name (void *initdata)


/* The structure which defines the mapping between shadeops and their
 * methods, init, and cleanup functions.
 */
typedef struct {
    char *prototype;
    char *init;
    char *cleanup;
} SHADEOP_SPEC;



/* A handy macro for declaration of the shadeop table. */
#define SHADEOP_TABLE(opname) DLLEXPORT SHADEOP_SPEC opname ## _shadeops[]

/* Here is an example of using this macro:
 * 
 *    SHADEOP_TABLE(sqr) = { { "float sqr_f(float)", "", "" },
 *                           { "color sqr_c(color)", "", "" },
 *                           { "", "", "" } // Blanks indicate end of list
 *                         };
 */





/* Internal PRMan representation of a string */
typedef struct {
    char *s;
    int   buflen;
    char  padding[4*sizeof(float)-sizeof(char *)-sizeof(int)];
} STRING_DESC;


#endif /* defined SHADEOP_H */
