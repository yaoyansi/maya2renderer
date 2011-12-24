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
#ifndef NDSPY_H
#define NDSPY_H

#ifndef DLLEXPORT
#if defined(_WIN32) || defined(_WINDOWS)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#endif /* ifndef DLLEXPORT */
    
#ifndef DLLIMPORT
#if defined(_WIN32) || defined(_WINDOWS)
#ifdef DLL 
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLIMPORT
#endif /* DLL */
#else
#define DLLIMPORT
#endif 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ri.h>


#define PkDspyMaxMsgSize 32760

#define PkDspyServerMsgOpen  (65 + 1)
#define PkDspyServerMsgImage (65 + 2)
#define PkDspyServerMsgData  (65 + 3)
#define PkDspyServerMsgQuery (65 + 4)
#define PkDspyServerMsgClose (65 + 5)
#define PkDspyServerMsgDeepData (65 + 6)

/*
PtDspyUnsigned64
PtDspySigned64
*/
typedef double PtDspyFloat64;
typedef float PtDspyFloat32;

#if defined(__mips)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__mips64)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__sparc)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__alpha)
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#elif defined(__ppc__)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#else
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#endif

typedef unsigned int PtDspyUnsigned32;
typedef int PtDspySigned32;

typedef unsigned short PtDspyUnsigned16;
typedef short PtDspySigned16;

typedef unsigned char PtDspyUnsigned8;
typedef char PtDspySigned8;

typedef PtDspyUnsigned32 PtDspyMsgLen;
typedef PtDspyUnsigned32 PtDspyServerMessage;



extern int _aiTypeLengths[];

#define PkDspyClassFloat 1
#define PkDspyClassInt 2

extern int _aiTypeSigned[];

extern int _aiTypeClass[];

#define PkDspyNone		0
#define PkDspyFloat32		1
#define PkDspyUnsigned32	2
#define PkDspySigned32		3
#define PkDspyUnsigned16	4
#define PkDspySigned16		5
#define PkDspyUnsigned8		6
#define PkDspySigned8		7
#define PkDspyString		8
#define PkDspyMatrix		9
#define PkDspyArrayBegin	10
#define PkDspyArrayEnd	        11

#define PkDspyMaskType		8191

#define PkDspyMaskOrder (PkDspyByteOrderHiLo | PkDspyByteOrderLoHi)
#define PkDspyShiftOrder	13
#define PkDspyByteOrderHiLo	8192
#define PkDspyByteOrderLoHi	16384


/*
 * PkDspyOpenPortCount controls the number of open display connections are used
 * by netrender/windows - or any process with an "internal" display server. 
 */
#define PkDspyOpenPortCount 1024


typedef struct
{
   char *name;
   unsigned type;
} PtDspyDevFormat;


typedef struct
{
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyFloat32 aspectRatio;
} PtDspySizeInfo;

typedef struct
{
  PtDspyUnsigned8 overwrite;
  PtDspyUnsigned8 interactive;
} PtDspyOverwriteInfo;
typedef struct
{
  PtDspyUnsigned8 redraw;
} PtDspyRedrawInfo;

typedef struct
{
  PtDspyUnsigned8 rewrite;
} PtDspyRewriteInfo;

typedef struct
{
    PtDspySigned32 xmin;
    PtDspySigned32 xmax;
    PtDspySigned32 ymin;
    PtDspySigned32 ymax;
} PtDspyNextDataInfo;

typedef struct {
    PtDspyUnsigned32 x;
    PtDspyUnsigned32 y;
} PtDspyRenderingStartQuery;

typedef struct {
    int canCheckpoint;
} PtDspySupportsCheckpointing;

typedef struct {
    int supportsPointClouds;
} PtDspyPointCloudQuery;

typedef struct {
    int supportsGrids;
} PtDspyGridQuery;

typedef enum
{
	PkSizeQuery,
	PkOverwriteQuery,
	PkNextDataQuery,
	PkRedrawQuery,
        PkRenderingStartQuery,
        PkSupportsCheckpointing,
	PkPointCloudQuery,
	PkGridQuery,
} PtDspyQueryType;

typedef enum
{
    	PkDspyGridConnected,
	PkDspyGridLines,
	PkDspyGridPoints
} PtDspyGridStyle;

typedef enum
{
	PkDspyErrorNone = 0,
	PkDspyErrorNoMemory,
	PkDspyErrorUnsupported,
	PkDspyErrorBadParams,
	PkDspyErrorNoResource,
	PkDspyErrorUndefined
} PtDspyError;

#define PkDspyFlagsWantsScanLineOrder 1
#define PkDspyFlagsWantsEmptyBuckets 2
#define PkDspyFlagsWantsNullEmptyBuckets 4
typedef struct
{
	int flags;
} PtFlagStuff;

typedef void *PtDspyImageHandle;



typedef void * PtDspyChannel;

typedef void * PtDspyOutput;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyUnsigned32 formatCount;
} PtDspyMsgOpen;
typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyUnsigned32 formatCount;
	PtDspyUnsigned32 paramCount;
} PtDspyMsgAddOutput;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 formatCount;
	PtDspyUnsigned32 paramCount;
} PtDspyMsgImage;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 xmin;
	PtDspyUnsigned32 xmax;
	PtDspyUnsigned32 ymin;
	PtDspyUnsigned32 ymax;
} PtDspyMsgData;


typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 xmin;
	PtDspyUnsigned32 xmax;
	PtDspyUnsigned32 ymin;
	PtDspyUnsigned32 ymax;
	PtDspyUnsigned32 datasize;
} PtDspyMsgDeepData;


typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyQueryType query;
	PtDspyUnsigned32 length;
} PtDspyMsgQuery;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
} PtDspyMsgClose;

typedef struct
{
    PtDspySigned8 vtype;
    PtDspySigned8 vcount;
    PtDspySigned8 byteorder;
    PtDspySigned8 XunusedpaddingX;
    PtDspyUnsigned32 nbytes;
    PtDspyUnsigned32 type;
} PtDspyMsgFormat;

typedef struct uparam {
        RtToken         name;
        char            vtype, vcount;
        RtPointer       value;
        int             nbytes;
} UserParameter;


#ifdef __cplusplus
extern "C" {
#endif
    
void DspyPrintFormat(FILE *fp,PtDspyDevFormat *format,int formatCount);

PtDspyDevFormat *
DspyCopyDevFormat(PtDspyDevFormat *f,int fc);

PtDspyError
DspyOpen(PtDspyChannel *pvChannel,
   char *szDevice,
   char *szConnectionName,
	int width,
	int height,
   int iFormatCount,
   PtDspyDevFormat *format);
PtDspyError
DspyReopen(PtDspyChannel *pvChannel, 	
	   char *szDevice,
	   char *szConnectionName,
	   int width,
	   int height,
	   int iFormatCount,
	   PtDspyDevFormat *format);


void DspyDeepByteSwap(PtDspyChannel pvChannel,
		      int numPixels,
		      char *data,
		      int dataSize,
		      PtDspyUnsigned32 *pixelOffsets,
		      PtDspyUnsigned32 *pixelSizes);

PtDspyError DspyDeepData(PtDspyChannel channel,
			     int xmin,int xmax,
			     int ymin,int ymax,
			     char *data,
			     int datasize,
			     PtDspyUnsigned32 *pixeloffsets,
			     PtDspyUnsigned32 *pixelsizes);
    
void DspyCloseOutput(PtDspyChannel channel);

PtDspyError DspyAddOutput(PtDspyChannel *channel,
			  int width,int height,
			  char *target,
			  char *filename,
			  int paramCount,
			  UserParameter *parameters,
			  int formatCount,
			  PtDspyDevFormat *format);

PtDspyError DspyAddPointCloudOutput(PtDspyChannel *channel,
			  int width,int height,
			  char *target,
			  char *filename,
			  int paramCount,
			  UserParameter *parameters,
			  int formatCount,
			  PtDspyDevFormat *format,
			  int *gridcapable);
    

PtDspyError
DspyImage(PtDspyChannel pvChannel,
	char *target,
	char *filename,
	int paramCount,
	UserParameter *parameters,
	int iFormatCount,
	PtDspyDevFormat *format);
PtDspyError
DspyData(PtDspyChannel pvChannel,
	int xmin,
	int xmax,
	int ymin,
	int ymax,
	unsigned char *data);
PtDspyError
DspyQuery(PtDspyChannel pvChannel,
	PtDspyQueryType querytype,
	int datalen,
	void *data);
PtDspyError
DspyClose(PtDspyChannel pvChannel);
PtDspyError
DspyFlush(PtDspyChannel *pvChannel);


typedef PtDspyError
	(*PtDspyOpenFuncPtr)(PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyWriteFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		int entrysize,
		const unsigned char *data);

typedef PtDspyError
	(*PtDspyDeepWriteFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		char *data,
                int datasize,
		PtDspyUnsigned32 *pixeloffsets,
		PtDspyUnsigned32 *pixelsizes);

typedef PtDspyError
	(*PtDspyCloseFuncPtr)(PtDspyImageHandle);
typedef PtDspyError
	(*PtDspyFlushFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyReopenFuncPtr)(PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyDelayCloseFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyQueryFuncPtr)(PtDspyImageHandle,
	   PtDspyQueryType,
	   int ,
	   void *);


DLLIMPORT PtDspyError DspyRegisterInternalImageDriver(const char *name,
					    const PtDspyOpenFuncPtr pOpen,
					    const PtDspyWriteFuncPtr pWrite,
					    const PtDspyCloseFuncPtr pClose,
					    const PtDspyQueryFuncPtr pQuery);




DLLIMPORT void
DspyMemReverseCopy(unsigned char *t, const unsigned char *s, int len);
DLLIMPORT void
DspyMemReverse(unsigned char *t, int len);



DLLIMPORT PtDspyError
DspyFindStringInParamList(const char *string,
	char **result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyFindMatrixInParamList(const char *string,
	float *result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyFindFloatInParamList(const char *string,
	float *result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyFindFloatsInParamList(const char *string,
	int *resultCount,
	float *result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyFindIntInParamList(const char *string,
	int *result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyFindIntsInParamList(const char *string,
	int *resultCount,
	int *result,
	int paramCount,
	const UserParameter *parameters);
DLLIMPORT PtDspyError
DspyReorderFormatting(int formatCount,
	PtDspyDevFormat *format,
	int outFormatCount,
	const PtDspyDevFormat *outFormat);

DLLIMPORT void DspyError(const char *module, const char *fmt, ...);


DLLEXPORT PtDspyError
DspyImageOpen(PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

DLLEXPORT PtDspyError
DspyImageData(PtDspyImageHandle image,
		int xmin,
		int xmax,
		int ymin,
		int ymax,
		int entrysize,
		const unsigned char *data);
 
DLLEXPORT PtDspyError
DspyImageClose(PtDspyImageHandle);

DLLEXPORT  PtDspyError
DspyImageReopen(PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

DLLEXPORT PtDspyError
DspyImageDelayClose(PtDspyImageHandle);

DLLEXPORT PtDspyError
DspyImageQuery(PtDspyImageHandle,
	   PtDspyQueryType,
	   int ,
	   void *);

DLLEXPORT PtDspyError
DspyImageDeepData(PtDspyImageHandle pvImage,
		  int xmin, int xmax, int ymin, int ymax,
		  char *data,int datasize,
		  int *pixeloffsets,
		  int *pixelsizes);
    
#undef DLLEXPORT


#ifdef __cplusplus
}
#endif

#endif /* ndef NDSPY_H */





