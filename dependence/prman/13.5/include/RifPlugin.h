#ifndef Rif_h
#define Rif_h
/* $Revision: #1 $ ($Date: 2007/07/06 $) */
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
 * RifPlugin.h represents the public interface to Ri Filter support.
 *	Plug-in Ri Filter developers should include this file
 *  	and implement the RifManufactureFilter call. Note
 *	that this file requires c++.
 */
#include <stdarg.h>
#include "RifFilter.h"

#if (defined(_WIN32) || defined(_WINDOWS)) && defined(DLL)
#ifndef DLLIMPORT
#define DLLIMPORT __declspec(dllimport)
#endif
#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif
#else
#ifndef DLLIMPORT
#define DLLIMPORT
#endif
#ifndef DLLEXPORT
#define DLLEXPORT
#endif
#endif

/* required of a Ri Filter plug-in *---------------------------------*/
			/*
			 * RifPlugin:
			*    all plug-in Ri Filters must subclass
			*   this pure-virtual class. Your subclass
			*   can have any number of RifFilter objects
			*   and can choose which to return based
			*   on its own state.
			*/
class RifPlugin
{
public:
    virtual     	~RifPlugin() {} /* virtual destructor */
    virtual RifFilter & GetFilter() =  0;
};

#ifdef __cplusplus
extern "C" {
#endif
    	    	    	/* RifPluginManufacture  :
			 *  Filter plugin-ins must implement
			 *  the RifPluginManufacture procedure.
			 *  This procedure constructs an instance 
			 *  of a RifPlugin subclass.
		    	 */
DLLEXPORT RifPlugin *	RifPluginManufacture(int argc, char **argv);


/* runtime services available to Ri Filter plug-ins----------------------*/
			/*
		 	 * These entrypoints are available to
			 * Filters to access server functionality
			 * and state.
			 */
    	    	    	typedef enum
			{
			    k_RifParseNextLayer,
			    k_RifParseThisLayer,
			    k_RifParseFirstLayer
			} RifParseMode;
DLLIMPORT RtVoid    	RifParseFile(const char *filename, RifParseMode m);
DLLIMPORT RtVoid    	RifParseBuffer(const char *buf, 
    	    	    	    	unsigned size,
    	    	    	    	RifParseMode m);
			typedef enum
			{
			    k_RifFloat=0,
			    k_RifPoint,
			    k_RifColor,
			    k_RifInteger,
			    k_RifString,
			    k_RifVector,
			    k_RifNormal,
			    k_RifHPoint,
			    k_RifMatrix,
			    k_RifMPoint
			} RifTokenType;
			typedef enum
			{
			    k_RifConstant=0,
			    k_RifUniform,
			    k_RifVarying,
			    k_RifVertex,
			    k_RifFaceVarying
			} RifTokenDetail;
DLLIMPORT RtInt		RifGetDeclaration(RtToken nm, 
				RifTokenType *,
				RifTokenDetail *,
				int *arraylen);
			typedef enum
			{
			    k_RifRIB,
			    k_RifRenderer
			} RifEmbedding;
DLLIMPORT RifEmbedding	RifGetEmbedding();
DLLIMPORT RtVoid	RifGetChainInfo(RtInt *current, 
    	    	    	    	RtInt *total );
DLLIMPORT void *   	RifGetCurrentPlugin();

#ifdef __cplusplus
}
#endif

#endif
