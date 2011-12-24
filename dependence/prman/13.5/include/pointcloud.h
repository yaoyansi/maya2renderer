/* $Revision: #2 $  
 * (Pixar - RenderMan Division)
 * $Date: 2007/10/01 $ 
 */
/*
** Copyright (c) 2004 PIXAR.  All rights reserved.  This program or
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

#ifndef _POINTCLOUD_
#define _POINTCLOUD_


typedef void *PtcPointCloud;

#ifdef __cplusplus
extern "C" {
#endif

/* Point cloud API version number */
#define RMAN_POINTCLOUD_API_VERSION 3

/* Point cloud API */

extern PtcPointCloud PtcCreatePointCloudFile(char *filename,
	int nvars, char **vartypes, char **varnames,
        float *world2eye, float *world2ndc, float *format);
extern int PtcWriteDataPoint(PtcPointCloud pointcloud,
	float *point, float *normal, float radius, float *data);
extern void PtcFinishPointCloudFile(PtcPointCloud pointcloud);

extern PtcPointCloud PtcOpenPointCloudFile(char *filename,
	int *nvars, char **vartypes, char **varnames); // superceded
extern PtcPointCloud PtcSafeOpenPointCloudFile(char *filename);
extern int PtcGetPointCloudInfo(PtcPointCloud pointcloud,
        char *request, void *result);
extern int PtcReadDataPoint(PtcPointCloud pointcloud,
	float *point, float *normal, float *radius, float *data);
extern void PtcClosePointCloudFile(PtcPointCloud pointcloud);

#ifdef __cplusplus
}
#endif

#endif /* _POINTCLOUD_ */
