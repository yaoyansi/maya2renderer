/* $Revision: #1 $  (Pixar - RenderMan Division)  $Date: 2007/07/06 $ */
/*
** Copyright (c) 2000-2006 PIXAR.  All rights reserved.  This program or
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
** Pixar Animation Studios
** 1200 Park Ave
** Emeryville, CA  94608
*/
#ifndef _RX_H
#define _RX_H
#include <ri.h>
#include <stdio.h> 		/* for FILE */

#ifndef DLLIMPORT
#if defined(_WIN32) || defined(_WINDOWS)
#ifdef DLL
#define DLLIMPORT extern __declspec(dllimport)
#else
#define DLLIMPORT
#endif /* DLL */
#else
#define DLLIMPORT
#endif 
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/*
** Public (DSO) interface for obtaining RixInterface objects (C++ only).
**
** A pointer to the global RixContext is returned, from which RixInterface
** objects can be obtained.
*/
#ifdef __cplusplus
DLLIMPORT extern class RixContext *RxGetRixContext();
#endif 

/*
** Public (DSO) interface for creating unique strings 
**
** Create a unique string based on the UUID and put the null-terminated string
** into the variable "sixty_four_chars_buffer".
*/

DLLIMPORT extern void RxUUIDCreateString( char *sixty_four_chars_buffer );

/*
** Public (DSO) interface for noise.
*/
DLLIMPORT extern RtInt RxNoise(int inDimension, float *in,
		     int outDimension, float *out);

DLLIMPORT extern RtInt RxPNoise(int inDimension, float *in, float *period,
		      int outDimension, float *out);

DLLIMPORT extern RtInt RxCellNoise(int inDimension, float *in,
			 int outDimension, float *out);

/*
** RxAttribute, RxOption, and RxRendererInfo return the
** current values of the named Attribute or Option.
**
** The caller passes in a buffer and it is filled-in with the
** resulting requested info.  Return value is 0 on success, or
** -1 if name can't be found, or N if the supplied buffer was
** too short and needs to be at least N bytes long.  Caller
** supplies the addresses of several other return values which
** are filled in:  resulttype is the RxInfoType_t of the values
** put into the result buffer, and resultcount is the number of
** those (multibyte) items.
*/

typedef enum {
    RxInfoFloat, RxInfoInteger, RxInfoStringV, RxInfoColor,
    RxInfoNormal, RxInfoVector, RxInfoPoint, RxInfoHPoint,
    RxInfoMPoint, RxInfoMatrix
} RxInfoType_t;

DLLIMPORT extern int RxOption (const char *name, void *result, int resultlen,
				RxInfoType_t *resulttype, int *resultcount);
DLLIMPORT extern int RxAttribute (const char *name, void *result, int resultlen,
				RxInfoType_t *resulttype, int *resultcount);
DLLIMPORT extern int RxRendererInfo (const char *name, void *result,
				     int resultlen, RxInfoType_t *resulttype,
				     int *resultcount);
/*
** Public (DSO) interface for textures.
*/
DLLIMPORT extern int RxEnvironmentPointsV(RtString filename, RtInt nPoints, 
        RtInt firstchannel, RtInt nchannels, 
        RtFloat *dir0, RtFloat *dir1, RtFloat *dir2, RtFloat *dir3,
	RtFloat *result, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxEnvironmentPoints(RtString filename, RtInt nPoints,
        RtInt firstchannel, RtInt nchannels, 
        RtFloat *dir0, RtFloat *dir1, RtFloat *dir2, RtFloat *dir3,
	RtFloat *result, ...);

DLLIMPORT extern int RxEnvironmentV(RtString filename, RtInt firstchannel,
	RtInt nchannels, RtPoint dir0, RtPoint dir1, RtPoint dir2, RtPoint dir3,
	RtFloat *result, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxEnvironment(RtString filename, RtInt firstchannel,
	RtInt nchannels, RtPoint dir0, RtPoint dir1, RtPoint dir2, RtPoint dir3,
	RtFloat *result, ...);

DLLIMPORT extern int RxShadowPointsV(RtString filename, RtInt nPoints, 
        RtInt firstchannel,
	RtFloat *P0, RtFloat *P1, RtFloat *P2, RtFloat *P3,
	RtFloat *result, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxShadowPoints(RtString filename, RtInt nPoints, 
        RtInt firstchannel,
	RtFloat *P0, RtFloat *P1, RtFloat *P2, RtFloat *P3, RtFloat *result, ...);

DLLIMPORT extern int RxShadowV(RtString filename, RtInt firstchannel,
	RtPoint P0, RtPoint P1, RtPoint P2, RtPoint P3,
	RtFloat *result, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxShadow(RtString filename, RtInt firstchannel,
	RtPoint P0, RtPoint P1, RtPoint P2, RtPoint P3, RtFloat *result, ...);

DLLIMPORT extern int RxSourceShadowV(RtString filename, RtInt firstchannel,
                           RtPoint P0, RtPoint P1, RtPoint P2, RtPoint P3,
                           RtPoint sourceP0, RtPoint sourceP1,
                           RtPoint sourceP2, RtPoint sourceP3,
                           RtFloat *result, RtInt n,
                           RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxSourceShadow(RtString filename, RtInt firstchannel,
                          RtPoint P0, RtPoint P1, RtPoint P2, RtPoint P3,
                          RtPoint sourceP0, RtPoint sourceP1,
                          RtPoint sourceP2, RtPoint sourceP3,
                          RtFloat *result, ...);

DLLIMPORT extern int RxTexturePointsV(RtString filename, RtInt nPoints,
        RtInt firstchannel, RtInt nchannels, RtFloat *s0, RtFloat *t0, RtFloat *s1, RtFloat *t1, 
        RtFloat *s2, RtFloat *t2, RtFloat *s3, RtFloat *t3, RtFloat *result, RtInt n, RtToken tokens[],
	RtPointer parms[]);

DLLIMPORT extern int RxTexturePoints(RtString filename, RtInt nPoints,
        RtInt firstchannel, RtInt nchannels, RtFloat *s0, RtFloat *t0, RtFloat *s1, RtFloat *t1, 
        RtFloat *s2, RtFloat *t2, RtFloat *s3, RtFloat *t3, RtFloat *result, ...);

DLLIMPORT extern int RxTextureV(RtString filename, RtInt firstchannel, RtInt nchannels,
	RtFloat s0, RtFloat t0, RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2,
	RtFloat s3, RtFloat t3, RtFloat *result, RtInt n, RtToken tokens[],
	RtPointer parms[]);

DLLIMPORT extern int RxTexture(RtString filename, RtInt firstchannel, RtInt nchannels,
	RtFloat s0, RtFloat t0, RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2,
	RtFloat s3, RtFloat t3, RtFloat *result, ...);

DLLIMPORT extern int RxTexture3dV(RtString filename,
        RtPoint point, RtNormal normal, RtFloat filterradius,
        RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxTexture3d(RtString filename,
        RtPoint point, RtNormal normal, RtFloat filterradius, ...);

DLLIMPORT extern int RxBake3dV(RtString filename,
        RtPoint point, RtNormal normal, RtFloat radius, 
        RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern int RxBake3d(RtString filename,
        RtPoint point, RtNormal normal, RtFloat radius, ...);

DLLIMPORT extern int RxTextureInfo(const char *filename, const char *attrname, void *result,
                                   int resultlen, RxInfoType_t *resulttype, int *resultcount);

DLLIMPORT extern int RxTextureGetData(const char *filename, int numchannels, int *chanids, int mipmaplevel, int face, void *result);



    

/*
** Public (DSO) interface for getting RIB context.
**
** Copies the linenumber of the current position in the input RIB to the
** int at location pointed to by linenumber.
** Copies the address of a string containing the current RIB filename to the
** pointer at the location pointed to by filename.  This string memory is owned
** by the renderer and should not be deallocated by a DSO.  If no RIB file name
** is available, *filename is set to NULL.
** Returns 0 if successful, 1 otherwise.
*/

DLLIMPORT extern int RxGetRIBFileContext(int *linenumber, char **filename);

/*
** Public (DSO) interface for transforming points
**
** Take the point array p, and transform it from the "from"
** space to the "to" space.
*/
DLLIMPORT extern RtInt RxTransformPoints(RtToken fromspace, RtToken tospace,
	                           RtInt n, RtPoint p[], RtFloat time);
DLLIMPORT extern RtInt RxTransform(RtToken fromspace, RtToken tospace,
       				RtFloat time, RtMatrix m);

    
#ifdef  __cplusplus
}
#endif

#endif /* ndef _RX_H */
