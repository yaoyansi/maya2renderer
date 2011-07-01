/*---------------------------------------------------------------------------------------------
	This file is part of Luna - the elvish ray renderer plug-in for Maya.
	Copyright (C) 2010  yaoyansi

	Luna is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Luna is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------

File		:	MayaConnection.h
Classes		:	
Description	:	interface between maya and elvishray, 
				handles the callbacks from elvishray.
Comments	:	
History		:	Created by yaoyansi, 2010.04.16.

---------------------------------------------------------------------------------------------*/

#ifndef _MAYA_CONNECTION_
#define _MAYA_CONNECTION_

#include "../log/prerequest_maya.h"
#include <core/include/connection.h>


class MayaConnection : public e_Connection
{
public:
	//interfaces for maya
	MStatus startRender( unsigned int width,
						unsigned int height,
						bool doNotClearBackground = false,
						bool immediateFeedback = false );
	MStatus endRender();
	unsigned int width;
	unsigned int height;


	// interfaces for elvishray
	virtual void	Print( const int code, const int severity, const char *message );
	virtual bool	Progress( const float percent );
	virtual void	ClearTile( const int left, const int right, 
								const int top, const int bottom );
	virtual void	UpdateTile( e_FrameBufferCache *colorFrameBuffer, 
								e_FrameBufferCache *opacityFrameBuffer, 
								std::vector< e_FrameBufferCache * > *frameBuffers, 
								const int left, const int right, 
								const int top, const int bottom );
	virtual void	DrawPixel( const int x, const int y, const Vector3f & color );
	virtual void	UpdateSubWindow( const int left, const int right, 
									const int top, const int bottom );

	//
public:
	static MayaConnection* getInstance();
	static void  delInstance();
	virtual ~MayaConnection();

protected:
	MayaConnection();
	static MayaConnection *m_instance;

	bool isInteractiveRenderingMode();
};

#endif //_MAYA_CONNECTION_
