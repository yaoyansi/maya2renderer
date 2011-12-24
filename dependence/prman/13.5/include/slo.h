/* $Revision: #1 $  (Pixar - RenderMan Division)  $Date: 2007/07/06 $ */
/*
** Copyright (c) 2000 PIXAR.  All rights reserved.  This program or
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
** 1200 Park Ave.
** Emeryville, CA  94608
*/
#ifndef _SLO_
#define _SLO_

typedef enum {
    SLO_TYPE_UNKNOWN,
    SLO_TYPE_POINT,
    SLO_TYPE_COLOR,
    SLO_TYPE_SCALAR,
    SLO_TYPE_STRING,
/* The following types are primarily used for shaders */
    SLO_TYPE_SHADER,
    SLO_TYPE_SURFACE,
    SLO_TYPE_LIGHT,
    SLO_TYPE_DISPLACEMENT,
    SLO_TYPE_VOLUME,
/* The following are variable types added since RISpec 3.1 */
    SLO_TYPE_VECTOR,
    SLO_TYPE_NORMAL,
    SLO_TYPE_MATRIX
    } SLO_TYPE;

typedef enum {
    SLO_STOR_UNKNOWN,
    SLO_STOR_CONSTANT,
    SLO_STOR_VARIABLE,
    SLO_STOR_TEMPORARY,
    SLO_STOR_PARAMETER,
    SLO_STOR_OUTPUTPARAMETER,
    SLO_STOR_GSTATE,
    SLO_STOR_METHODINPUT,
    SLO_STOR_METHODOUTPUT
    } SLO_STORAGE;

typedef enum {
    SLO_DETAIL_UNKNOWN,
    SLO_DETAIL_VARYING,
    SLO_DETAIL_UNIFORM
    } SLO_DETAIL;

typedef struct {
    float	xval;
    float	yval;
    float	zval;
    } POINT3D;

typedef float SCALAR;

typedef struct slovissymdef {
    char *svd_name;
    SLO_TYPE svd_type;
    SLO_STORAGE svd_storage;
    SLO_DETAIL svd_detail;
    char *svd_spacename;
    union {
	POINT3D	*pointval;
	SCALAR	*scalarval;
	char	*stringval;
	float   *matrixval;
    } svd_default;
    union svd_defaultvalu {
	POINT3D	svd_pointval;
	SCALAR	svd_scalarval;
    } svd_defaultval;
    unsigned svd_valisvalid : 1;
    int svd_arraylen;
} SLO_VISSYMDEF;

#define NULL_SLOVISSYMDEF ((SLO_VISSYMDEF *) 0)

#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void Slo_SetPath(char *path);
extern const char *Slo_GetPath(void);
extern int Slo_SetShader(char *name);
extern const char *Slo_GetName(void);
extern SLO_TYPE Slo_GetType(void);
extern int Slo_HasMethod(const char *name);
extern const char** Slo_GetMethodNames(void);
extern int Slo_GetNArgs(void);
extern SLO_VISSYMDEF *Slo_GetArgByName(char *name);
extern SLO_VISSYMDEF *Slo_GetArgById(int id);
extern SLO_VISSYMDEF *Slo_GetArrayArgElement(SLO_VISSYMDEF *array, int index);
extern void Slo_EndShader(void);
extern char *Slo_TypetoStr(SLO_TYPE type);
extern char *Slo_StortoStr(SLO_STORAGE storage);
extern char *Slo_DetailtoStr(SLO_DETAIL detail);
extern const char* Slo_GetMetaData(const char* name);
extern const char** Slo_GetAllMetaData();
extern const char** Slo_GetPlugins();

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _SLO_ */
