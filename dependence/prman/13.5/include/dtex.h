/*
** Copyright (c) 2003 PIXAR.  All rights reserved.  This program or
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

/*
 * libdtex
 *
 * This library provides the structures and functions necessary to create,
 * load, and modify deep texture map files.  It maintains a tile cache
 * under the covers, making it possible to work on files without loading
 * them entirely into memory.
 *
 * The API supports an arbitrary number of images in a single file, each
 * with its own resolution, tile size, and view matrices.
 *
 * The library can read and write old deep shadow files in addition to
 * newer, more general deep texture files.  Deep shadow files are
 * limited to a single sub-image, but otherwise have the same API as the
 * newer interface.
 */

#ifndef DTEX_H
#define DTEX_H

/* The following struct types aren't exported; users may only
   access members through the API calls defined below. */

typedef struct DtexFile DtexFile;
typedef struct DtexImage DtexImage;
typedef struct DtexPixel DtexPixel;
typedef struct DtexCache DtexCache;
typedef struct DtexDeepFilter DtexDeepFilter;

/* DtexCreate and DtexOpen let the user specify their
   own file access functions, in case read() and write() aren't
   good enough.  Following are the types for these functions: */

typedef void *(*DtexCreateFunc)(const char *name);
typedef void *(*DtexOpenFunc)(const char *name, const char *mode);
typedef long (*DtexReadFunc)(void *handle, char *data, long seek, long size);
typedef long (*DtexWriteFunc)(void *handle, char *data, long seek, long size);
typedef void (*DtexCloseFunc)(void *handle);

/* DtexAccessor encapsulates the various file access functions.  A
   pointer to one of these can be passed to DtexCreate() or
   DtexOpen() if nonstandard file access methods are needed. */

typedef struct DtexAccessor 
{
    DtexCreateFunc createFunc;    /* function to create a file */
    DtexOpenFunc openFunc;        /* function to open a file */
    DtexReadFunc readFunc;        /* function to read from a file handle */
    DtexWriteFunc writeFunc;      /* function to write to a file handle */
    DtexCloseFunc closeFunc;      /* function to close a file handle */
} DtexAccessor;


/* Tile compression type. */
typedef enum DtexCompression
{
    DTEX_COMPRESSION_NONE = 0,
    DTEX_COMPRESSION_RLE = 2,
    DTEX_COMPRESSION_LZW = 3,
    DTEX_COMPRESSION_HUFFMAN = 5,
    DTEX_COMPRESSION_ZIP = 6
} DtexCompression; 

/* Type of data stored with each pixel. (Note that the depth is always
   stored as a float. */
typedef enum DtexDataType
{
    DTEX_TYPE_BYTE = 1,
    DTEX_TYPE_SHORT = 2,
    DTEX_TYPE_WORD = 3,
    DTEX_TYPE_FLOAT = 4
} DtexDataType;

/* Error codes: */

enum{
    DTEX_TILECOMPRESSION  = -10,  /* Something happened during tile compression */
    DTEX_UNFINISHED  =  -9,   /* Illegal operation on pixel with unresolved
				 compression state */
    DTEX_RANGE       =  -8,   /* Out of range parameter */
    DTEX_NOMEM       =  -7,   /* Ran out of memory */
    DTEX_EMPTY       =  -6,   /* Illegal operation on an empty structure */
    DTEX_NOIMAGE     =  -5,   /* The specified image was not found */
    DTEX_UNSUPPORTED =  -4,   /* The specified operation is not supported. */
    DTEX_BADFILE     =  -3,   /* File was corrupt */
    DTEX_NOFILE      =  -2,   /* File was not found or was invalid */
    DTEX_ERR         =  -1,   /* File was not found or was invalid */
    DTEX_NOERR       =   0    /* No worries */
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 *********************************************************************
 *  CACHE FUNCTIONS:
 *********************************************************************
 *
 * The following functions are used to maintain deep texture tile
 * caches.
 */

/* ----------------------------------------------------------------- */

extern DtexCache * DtexCreateCache(int numTiles,
				   DtexAccessor *accessor);
/*
 * create a new tile cache.  accessor specifies a set of I/O functions
 * to use upon faults.  If accessor is NULL, standard system calls
 * are used.
 */


/* ----------------------------------------------------------------- */

extern int DtexDestroyCache(DtexCache *c);

/* ----------------------------------------------------------------- */

extern int DtexSyncCache(DtexCache *dsc);

/*
 * write out all modified tiles of all files in the cache, causing the
 * files on disk to reflect any changes that have been made.
 */

/* ----------------------------------------------------------------- */

/*
 *********************************************************************
 *  FILE OPENING/CLOSING FUNCTIONS:
 *********************************************************************
 *
 * The following functions are used to create new deep texture files,
 * or to open existing deep texture files.
 */

/* ----------------------------------------------------------------- */

extern int DtexOpenFile(const char *name,
			const char *mode,
			DtexCache *cache,
			DtexFile **result);
/* 
 * Open a deep texture file with the given filename, managed by the
 * given cache.
 */

/* ----------------------------------------------------------------- */

extern int DtexCreateFile(const char *name,
			  DtexCache *cache,
			  DtexFile **result);
/* 
 * Create a new deep texture file with the given filename, managed by the
 * given cache.
 */

/* ----------------------------------------------------------------- */

extern int DtexAddImage(DtexFile *f,
			const char *name,
			int numChan,
			int w, int h,
			int tw, int th,      /* tile width and height */
			float *NP,
			float *Nl,
			enum DtexCompression compression,
			enum DtexDataType datatype,
			DtexImage **result);
/*
 * Add an image to the given file.
 */

/* ----------------------------------------------------------------- */

extern int DtexCountImages(DtexFile *f);

/*
 * Return the number of images in the given file.
 */

/* ----------------------------------------------------------------- */

/* 
 * If the given file contains an image with the given name, return a
 * pointer to it.  Returns DTEX_NOIMAGE if the given image doesn't exist. 
 * The resulting pointer is guaranteed to be valid until DtexClose() is
 * called on the containing
 * file.
 */

extern int DtexGetImageByName(DtexFile *f,
			      const char *name,
			      DtexImage **result);

/* ----------------------------------------------------------------- */

/*
 * Return the nth image from the given file.  Returns DTEX_NOFILE
 * if the file doesn't exist, or DTEX_NOIMAGE if the given image doesn't
 * exist.  The resulting pointer is guaranteed to be valid until
 * DtexClose() is called on the containing file.
 */

extern int DtexGetImageByIndex(DtexFile *f,
			       int index,
			       DtexImage **result);

/* ----------------------------------------------------------------- */

extern int DtexClose(DtexFile *ds);
/*
 * close a deep texture file, writing out all modified tiles.
 */

/* ----------------------------------------------------------------- */

extern int DtexSync(DtexFile *ds);

/*
 * write out all modified tiles of deep texture "ds", causing the
 * file on disk to reflect any changes that have been made.
 */

/* ----------------------------------------------------------------- */

/*
 *********************************************************************
 *  FILE ACCESS FUNCTIONS:
 *********************************************************************
 *
 * The following functions let the user access and modify the
 * contents of an open deep texture file.
 */

/* ----------------------------------------------------------------- */

extern int DtexWidth(DtexImage *i);
/*
 * return the width of the given image in pixels
 */

/* ----------------------------------------------------------------- */

extern char *DtexImageName(DtexImage *i);
/*
 * return the name of the given image.  The resulting pointer is
 * guaranteed to be valid until DtexClose() is called on the containing
 * file.
 */

/* ----------------------------------------------------------------- */

extern int DtexNumChan(DtexImage *i);
/*
 * return the number of channels in the given image
 */

/* ----------------------------------------------------------------- */

extern int DtexHeight(DtexImage *i);
/*
 * return the height of the given image in pixels
 */

/* ----------------------------------------------------------------- */

extern int DtexTileWidth(DtexImage *i);
/*
 * return the width of the tiles in the given image, in pixels
 */

/* ----------------------------------------------------------------- */

extern int DtexTileHeight(DtexImage *i);
/* 
 * return the height of the tiles in the given deep texture, in pixels
 */

/* ----------------------------------------------------------------- */

extern int DtexNP(DtexImage *i, float *NP);
/*
 * copy the projection matrix from the given image to NP.
 */

/* ----------------------------------------------------------------- */

extern int DtexNl(DtexImage *i, float *Nl);
/*
 * copy the light-space matrix from the given image to Nl.
 */

/* ----------------------------------------------------------------- */

extern DtexCompression DtexGetCompression(DtexImage *i);
/*
 * return the compression type of the image.
 */

/* ----------------------------------------------------------------- */

extern DtexDataType DtexGetDataType(DtexImage *i);
/*
 * return the data type of the image.
 */

/* ----------------------------------------------------------------- */

extern int DtexSetPixelData(DtexImage *img,
			    int x, int y,
			    int numChan,
			    int numPoints,
			    float *data);
/*
 * copy the given pixel data into pixel x,y of the specified image. 
 * numChan indicates how many channels of data are being provided,
 * and numPoints indicates how many points there are.  data should
 * point to numPoints*(numChan+1) floats.
 */

/* ----------------------------------------------------------------- */

extern int DtexSetPixel(DtexImage *img,
			int x, int y,
			DtexPixel *pix);
/*
 * copy the given pixel into pixel x,y of the specified image.  pix
 * must have either the same number of channels as img, or one channel.
 *
 * If pix has any unresolved compression state, DTEX_ERR is returned.
 * Call DtexFinishPixel before you use DtexSetPixel.
 */

/* ----------------------------------------------------------------- */

extern int DtexGetPixel(DtexImage *img,
			int x, int y,
			DtexPixel *pix);
/*
 * copy the pixel at position x,y in "ds" into the given pixel
 * structure.  The pixel structure is resized if necessary, and if
 * the number of channels in pix is different than the number of
 * channels in img, pix is modified to match.
 *
 * Returns DTEX_NOERR if no error, DTEX_RANGE if the requested pixel
 * is outside the image, or DTEX_BADFILE if the file is found to be
 * corrupt.
 */

/* ----------------------------------------------------------------- */

extern int DtexEval(DtexImage *img,
		    int x, int y,
		    float z,
		    int n,
		    float *data);
/*
 * look up the pixel's interpolated value at depth z, and put the
 * result in data.  n must indicate how many floats are
 * allocated in data, and must be no less than the number of
 * channels in the image.
 */

/* ----------------------------------------------------------------- */

extern int DtexGetZRange(DtexImage *img,
			 int x, int y,
			 float *min,
			 float *max);
/*
 * computes the range over which the specified pixel is defined.
 * if the pixel is non-empty, the range is returned in min and max
 * and the function returns DTEX_NOERR.  If the pixel is empty, 
 * DTEX_EMPTY is returned and min and max are undefined.
 */

/* ----------------------------------------------------------------- */

extern int DtexGetMeanDepth(DtexImage *img,
			    int x, int y,
			    float *mean,
			    float *alpha);
/*
 * computes the mean depth found in the pixel and the overall
 * coverage.  This is useful for displaying deep images.
 */

/* ----------------------------------------------------------------- */

/*
 *********************************************************************
 *  PIXEL STRUCTURE FUNCTIONS:
 *********************************************************************
 *
 * Because deep texture pixels are varying in size, a pixel's storage
 * must be dynamically allocated.  This library
 * provides a type, DtexPixel, which allows users to build and evaluate
 * pixels.  The structure is fairly heavyweight because it stores
 * auxiliary information related to compression.  We don't recommend
 * allocating an entire image of these structures yourself; keep
 * a small number of DtexPixel's around, and use DtexSetPixel to
 * modify a DtexImage.
 *
 * The following functions let the user create, modify, and
 * destroy DtexPixel's.  Pixels may be cleared with DtexClearPixel().
 * New datapoints may be added (in increasing Z order) with
 * DtexAppendPixel().  If compression is used, a pixel must
 * be DtexFinish()'ed before lookups can be performed in the pixel.
 */

/* ----------------------------------------------------------------- */

extern DtexPixel * DtexMakePixel(int numChan);
/*
 * create a DtexPixel structure.  It should be destroyed with
 * DtexDestroyPixel, not free().
 */

/* ----------------------------------------------------------------- */

extern void DtexDestroyPixel(DtexPixel *pix);
/*
 * free a DtexPixel structure.
 */

/* ----------------------------------------------------------------- */

extern int DtexClearPixel(DtexPixel *pix, int numChan);
/*
 * set the specified pixel structure to be empty.  Its allocation
 * stays around, but the pixel is marked as empty.
 */

/* ----------------------------------------------------------------- */

extern int DtexEmptyPixel(DtexPixel *pix);

/*
 * Clear out all the allocation in the given pixel, but don't free
 * the pixel itself.
 */

/* ----------------------------------------------------------------- */

extern int DtexSpecifyPixel(DtexPixel *pix,int numChan,int numPoints,
			    float *data);

/*
 * Set the given pixel to have numChan channels and set its data
 * directly.  Assumes no compression.
 */

/* ----------------------------------------------------------------- */

extern int DtexIsPixelMonochrome(DtexPixel *p);

/*
 * Return 1 if the specific pixel has duplicates for all its values,
 * zero otherwise.  If the pixel has no control points, returns 1.
 */

/* ----------------------------------------------------------------- */

extern int DtexPixelGetNumChan(DtexPixel *pix);
/*
 * Return the number of channels in the pixel.
 */

/* ----------------------------------------------------------------- */

extern int DtexPixelGetNumPoints(DtexPixel *pix);
/*
 * Return the number of control points in the pixel.  Returns zero
 * if there are no control points, -1 if the point has unresolved
 * compression state.
 */

/* ----------------------------------------------------------------- */

extern int DtexPixelGetPoint(DtexPixel *pix, int i, float *z, float *data);
/*
 * Get the i'th control point in the given pixel.  If the indicated
 * control point is accessible, z and data are set, and DTEX_NOERR
 * is returned.  If the pixel does not exist, DTEX_NOPOINT is
 * returned and *z and *data are undefined.  If the pixel has
 * unresolved compression state, DTEX_UNFINISHED is returned and
 * *z and *data are undefined.
 */

/* ----------------------------------------------------------------- */

extern int DtexPixelSetPoint(DtexPixel *pix, int i, float z, float *data);

/*
 * Modify the i'th control point in the given pixel.  If the indicated
 * control point is accessible, and if the supplied z is legal,
 * the pixel is modified and DTEX_NOERR
 * is returned.  If the pixel does not exist, DTEX_NOPOINT is
 * returned.  If the pixel has unresolved compression state,
 * DTEX_UNFINISHED is returned and *z and *data are undefined.
 */

/* ----------------------------------------------------------------- */

extern int DtexCopyPixel(DtexPixel *dest,
			 DtexPixel *src);
/*
 * copy src to dest.  If dest has a different number of channels
 * than src, dest is modified to match. This includes current
 * compression state.
 */

/* ----------------------------------------------------------------- */

extern int DtexFinishPixel(DtexPixel *dest);
/*
 * If the specified pixel is in "compress mode" (non-zero compression),
 * this function finishes compression and sets compression error to zero.
 * This must be called before any lookups on the pixel structure.
 *
 * If the pixel already has a zero compression error, this function has
 * no effect.
 */

/* ----------------------------------------------------------------- */

extern int DtexAppendPixel(DtexPixel *pix,
			   float z,
			   int n,
			   float *data,
			   float error);
/*
 * add a data point to the end of the specified pixel.  n must
 * specify how many floats are stored in data, and must match
 * the number of channels in the pixel.
 */

/* ----------------------------------------------------------------- */

extern int DtexEvalPixel(DtexPixel *pix,
			 float z,
			 int n,
			 float *data);
/*
 * evaluate the pixel's function at depth z, and put the
 * result in data.  n must indicate how many floats are
 * allocated in data, and must be no less than the number of
 * channels in the image.
 */

/* ----------------------------------------------------------------- */

extern int DtexGetPixelZRange(DtexPixel *pix,
			      float *min,
			      float *max);
/*
 * computes the range over which the specified pixel is defined.
 * if the pixel is non-empty, the range is returned in min and max
 * and the function returns DTEX_NOERR.  If the pixel is empty, 
 * DTEX_EMPTY is returned and min and max are undefined.  If the pixel
 * has unresolved compression state, DTEX_UNFINISHED is returned and
 * min and max are undefined.
 */

/* ----------------------------------------------------------------- */

extern int DtexPrintPixel(DtexPixel *p);
/*
 * print a representation of the given pixel to stdout
 */

/* ----------------------------------------------------------------- */

extern int DtexAveragePixels(int n,
			     DtexPixel **pixels,
			     float *weights,
			     float error,
			     DtexPixel *result);
/*
 * compute the weighted pointwise average of the given pixels and put the
 * result in result.
 */

/* ----------------------------------------------------------------- */

extern void DtexPrintStats(void);

/* ----------------------------------------------------------------- */

/* Create a new Deep filter */

extern DtexDeepFilter *DtexCreateDeepFilter(void);

/* Destroy a new Deep filter */

extern void DtexDestroyDeepFilter(DtexDeepFilter *filter);

/*
 * Prepare the given filter to take samples.  numChan is the number of
 * channels (in addition to z) per delta.  numSamples is the number of
 * samples in the filter.  numDeltas is an array with numSamples values
 * indicating, for each sample, how many deltas are in that sample.
 * filterWeights is an array with numSamples floats indicating, for each
 * sample, what that sample's filterweight is.  totalNumDeltas is the
 * sum of the values in numDeltas.
 *
 * When this function is done, all the samples will be set up.  The
 * user can then run through and fill in the actual deltas.
 */

extern float *DtexGetDeepFilterData(DtexDeepFilter *filter,
				    int numChan,
				    int numSamples,
				    int *numDeltas,
				    float *filterWeights,
				    int totalNumDeltas);

/* ----------------------------------------------------------------- */

/* Execute the given filter to produce point data.  pointData must
   contain enough space to hold "totalNumDeltas" deltas as specified
   in DtexGetDeepFilterData.

   If assumeSmooth is non-zero, the computation will assume that the
   underlying function is smooth, and that any discontinuities encountered
   are part of the sampling error.  It will thus not try to reproduce
   discontinuities.

*/

extern int DtexComputeDeepPointData(DtexDeepFilter *filter,
				    float *pointData,
				    float error,
				    int assumeSmooth);

/* ----------------------------------------------------------------- */

/* Given a series of points, compress it. */

extern int DtexCompressPointData(float *pointData,
				 int numChan,
				 int numPoints,
				 float *result,
				 float error);

/* ----------------------------------------------------------------- */

/* Compress one pixel and put the result in another.  Doesn't work
 * in place.  (dest must not == src.)
 */

int
DtexCompressPixel(DtexPixel *src,DtexPixel *dest,float error);

/* ----------------------------------------------------------------- */

void
DtexQueryMemory(unsigned long *current,unsigned long *peak);

#ifdef __cplusplus
}
#endif

#endif /* DTEX_H */

