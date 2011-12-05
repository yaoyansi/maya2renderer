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
#include "../log/prerequest_std.h"
#include "../log/prerequest_maya.h"
#include <eiAPI/ei_connection.h>

class MayaConnection;

class eiMayaConnection {
public:
	eiConnection	base;
	MayaConnection	*object;
};

class MayaConnection
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
	virtual void	Print( const eiInt severity, const char *message );
	virtual bool	Progress( const eiScalar percent );
	virtual void	ClearTile( const eiInt left, const eiInt right, 
								const eiInt top, const eiInt bottom,
								const eiHostID host );
	virtual void	UpdateTile( eiFrameBufferCache *colorFrameBuffer, 
								eiFrameBufferCache *opacityFrameBuffer, 
								ei_array *frameBuffers, 
								const eiInt left, const eiInt right, 
								const eiInt top, const eiInt bottom );
	virtual void	DrawPixel( const eiInt x, const eiInt y, const eiVector *_color );
	virtual void	UpdateSubWindow( const eiInt left, const eiInt right, 
								const eiInt top, const eiInt bottom  );

	//
public:
	static MayaConnection* getInstance();
	static void  delInstance();
	virtual ~MayaConnection();

protected:
	MayaConnection();
	static MayaConnection *m_instance;

	bool isInteractiveRenderingMode();

public:
	eiMayaConnection connection;

protected:
	void setConnection();
};

#endif //_MAYA_CONNECTION_
