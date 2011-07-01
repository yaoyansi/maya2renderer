/*
**
** The contents of this file are subject to the Mozilla Public License Version 1.1 (the
** "License"); you may not use this file except in compliance with the License. You may
** obtain a copy of the License at http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis, WITHOUT
** WARRANTY OF ANY KIND, either express or implied. See the License for the specific
** language governing rights and limitations under the License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions created by
** Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
**
** Contributor(s): Berj Bannayan.
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
*/
#include <liqShader.h>

#include <algorithm>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>

#include <maya/MPlug.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MGlobal.h>
#include <maya/MPlugArray.h>
#include <maya/MFnMatrixData.h>

#include <lights.h>
#include <liquid.h>
#include <liqGlobalHelpers.h>
#include <liqMayaNodeIds.h>
#include <liqShaderFactory.h>
#include <liqTokenPointer.h>
#include <liqRibLightData.h>
#include <liqRibTranslator.h>
#include <liqExpression.h>

using namespace std;
using namespace boost;


liqShader::liqShader()
{
  //numTPV                = 0;
  name                  = "";
  file                  = "";
  rmColor[0]            = 1.0;
  rmColor[1]            = 1.0;
  rmColor[2]            = 1.0;
  rmOpacity[0]          = 1.0;
  rmOpacity[1]          = 1.0;
  rmOpacity[2]          = 1.0;
  hasShadingRate        = false;
  shadingRate           = 1.0;
  hasDisplacementBound  = false;
  displacementBound     = 0.0;
  outputInShadow        = false;
  hasErrors             = false;
  shader_type           = SHADER_TYPE_UNKNOWN;
  shaderSpace           = "";
  evaluateAtEveryFrame  = 0;
  tokenPointerArray.push_back( liqTokenPointer() ); // ENsure we have a 0 element
  shaderHandler         = liqShaderFactory::instance().getUniqueShaderHandler();
}

liqShader::liqShader( const liqShader& src )
{
  //numTPV               = src.numTPV;
  tokenPointerArray    = src.tokenPointerArray;
  name                 = src.name;
  file                 = src.file;
  rmColor[0]           = src.rmColor[0];
  rmColor[1]           = src.rmColor[1];
  rmColor[2]           = src.rmColor[2];
  rmOpacity[0]         = src.rmOpacity[0];
  rmOpacity[1]         = src.rmOpacity[1];
  rmOpacity[2]         = src.rmOpacity[2];
  hasShadingRate       = src.hasShadingRate;
  shadingRate          = src.shadingRate;
  hasDisplacementBound = src.hasDisplacementBound;
  displacementBound    = src.displacementBound;
  outputInShadow       = src.outputInShadow;
  hasErrors            = src.hasErrors;
  shader_type          = src.shader_type;
  shaderSpace          = src.shaderSpace;
  evaluateAtEveryFrame = src.evaluateAtEveryFrame;
  shaderHandler        = src.shaderHandler;
  m_mObject            = src.m_mObject;
}

liqShader & liqShader::operator=( const liqShader & src )
{
  //numTPV = src.numTPV;
  tokenPointerArray     = src.tokenPointerArray;
  name                  = src.name;
  file                  = src.file;
  rmColor[0]            = src.rmColor[0];
  rmColor[1]            = src.rmColor[1];
  rmColor[2]            = src.rmColor[2];
  rmOpacity[0]          = src.rmOpacity[0];
  rmOpacity[1]          = src.rmOpacity[1];
  rmOpacity[2]          = src.rmOpacity[2];
  hasShadingRate        = src.hasShadingRate;
  shadingRate           = src.shadingRate;
  hasDisplacementBound  = src.hasDisplacementBound;
  displacementBound     = src.displacementBound;
  outputInShadow        = src.outputInShadow;
  hasErrors             = src.hasErrors;
  shader_type           = src.shader_type;
  shaderSpace           = src.shaderSpace;
  evaluateAtEveryFrame = src.evaluateAtEveryFrame;
  shaderHandler        = src.shaderHandler;
  m_mObject            = src.m_mObject;
  return *this;
}


liqShader::liqShader( MObject shaderObj )
{
	MString rmShaderStr;
	MStatus status;
	MFnDependencyNode shaderNode( shaderObj );
	MPlug rmanShaderNamePlug = shaderNode.findPlug( MString( "rmanShaderLong" ) );
	rmanShaderNamePlug.getValue( rmShaderStr );
	shaderHandler = liqShaderFactory::instance().getUniqueShaderHandler();

	LIQDEBUGPRINTF( "-> Using Renderman Shader %s. \n", rmShaderStr.asChar() );

	unsigned numArgs;
	//numTPV = 0;
	hasShadingRate = false;
	hasDisplacementBound = false;
	outputInShadow = false;
	hasErrors = false;
	tokenPointerArray.push_back( liqTokenPointer() );
	m_mObject = shaderObj;

	// if this shader instance isn't currently used already then load it into the
	// lookup set it as my slo lookup
	name = shaderNode.name().asChar();
	file = rmShaderStr.substring( 0, rmShaderStr.length() - 5 ).asChar();

	rmColor[0]            = 1.0;
	rmColor[1]            = 1.0;
	rmColor[2]            = 1.0;
	rmOpacity[0]          = 1.0;
	rmOpacity[1]          = 1.0;
	rmOpacity[2]          = 1.0;

	liqGetSloInfo shaderInfo;


// commented out for it generates errors - Alf
	int success = ( shaderInfo.setShaderNode( shaderNode ) );
	if ( !success )
	{
		liquidMessage( "Problem using shader '" + string( shaderNode.name().asChar() ) + "'", messageError );
		rmColor[0] = 1.0;
		rmColor[1] = 0.0;
		rmColor[2] = 0.0;
		name = "plastic";
//		numTPV = 0;
		hasErrors = true;
	}
	else
	{
		/* Used to handling shading rates set in the surface shader,
		this is a useful way for shader writers to ensure that their
		shaders are always rendered as they were designed.  This value
		overrides the global shading rate but gets overridden with the
		node specific shading rate. */

		shader_type = shaderInfo.getType();
		// Set RiColor and RiOpacity
		status.clear();
		MPlug colorPlug = shaderNode.findPlug( "color" );
		if ( MS::kSuccess == status )
		{
			colorPlug.child(0).getValue( rmColor[0] );
			colorPlug.child(1).getValue( rmColor[1] );
			colorPlug.child(2).getValue( rmColor[2] );
		}

		status.clear();
		MPlug opacityPlug( shaderNode.findPlug( "opacity" ) );
		// Moritz: changed opacity from float to color in MEL
		if ( MS::kSuccess == status )
		{
		  opacityPlug.child(0).getValue( rmOpacity[0] );
		  opacityPlug.child(1).getValue( rmOpacity[1] );
		  opacityPlug.child(2).getValue( rmOpacity[2] );
		}

		status.clear();
		MPlug shaderSpacePlug( shaderNode.findPlug( "shaderSpace" ) );
		if ( MS::kSuccess == status )
		{
			shaderSpacePlug.getValue( shaderSpace );
		}

		status.clear();
		MPlug outputInShadowPlug( shaderNode.findPlug( "outputInShadow" ) );
		if ( MS::kSuccess == status )
		{
			outputInShadowPlug.getValue( outputInShadow );
		}

		status.clear();
		MPlug evaluateAtEveryFramePlug( shaderNode.findPlug( "evaluateAtEveryFrame" ) );
		if ( MS::kSuccess == status )
		{
			evaluateAtEveryFramePlug.getValue( evaluateAtEveryFrame );
		}

		// find the parameter details and declare them in the rib stream
		numArgs = shaderInfo.getNumParam();
		for (unsigned int i( 0 ); i < numArgs; i++ )
		{
			if( shaderInfo.isOutputParameter(i) )   // throw output parameters
			{
				continue;				
			}
			MString paramName = shaderInfo.getArgName(i);
			int arraySize = shaderInfo.getArgArraySize(i);
			SHADER_TYPE shaderType = shaderInfo.getArgType(i);
			SHADER_DETAIL shaderDetail = shaderInfo.getArgDetail(i);

			bool skipToken = false;
			if ( paramName == "liquidShadingRate" )
			{
				// BUGFIX: Monday 6th August - fixed shading rate bug where it only accepted the default value
				MPlug floatPlug = shaderNode.findPlug( paramName, &status );
				if ( MS::kSuccess == status )
				{
					float floatPlugVal;
					floatPlug.getValue( floatPlugVal );
					shadingRate = floatPlugVal;
				}
				else
					shadingRate = shaderInfo.getArgFloatDefault( i, 0 );
				
				hasShadingRate = true;
				continue;
			}
			
			switch ( shaderType )
			{
				case SHADER_TYPE_STRING:
				{
					MPlug stringPlug = shaderNode.findPlug( paramName, &status );
					if ( MS::kSuccess == status )
					{
						if( arraySize == 0 ) 
						{
							skipToken = true;
							liquidMessage2(messageWarning, "[liqShader] warning undefined string array size, not yet implemented...\n");
						}
						else if( arraySize > 0 ) 
						{
							bool isArrayAttr( stringPlug.isArray( &status ) );
							if ( isArrayAttr )
							{
								MPlug plugObj;
								tokenPointerArray.rbegin()->set( paramName.asChar(), rString, arraySize );
								for( unsigned int kk( 0 ); kk < (unsigned int)arraySize; kk++ )
								{
									plugObj = stringPlug.elementByLogicalIndex( kk, &status );
									if ( MS::kSuccess == status )
									{
										MString stringPlugVal;
										plugObj.getValue( stringPlugVal );
										MString stringVal = parseString( stringPlugVal );
										tokenPointerArray.rbegin()->setTokenString( kk, stringVal.asChar() );
									}
									else
									{
										liquidMessage2(messageError, "[liqShader] error while building param %d : %s \n", kk, stringPlug.name().asChar() );
									}
								}
							}
							else
							{
								liquidMessage2(messageError, "[liqShader] error while building string param %s assumed as an array but wasn't...\n", stringPlug.name().asChar() );
							}
						}
						else if( arraySize == -1 )
						{
							MString stringPlugVal;
							stringPlug.getValue( stringPlugVal );
							MStringArray textureTokensString;
							MStatus stat = stringPlugVal.split('.', textureTokensString);
							if(stat == MS::kSuccess)
							{
								MString textureExten(textureTokensString[textureTokensString.length()-1]);
								if(MString("tex")!=textureExten.toLowerCase()){
									stringPlugVal += ".tex";
								}
							}
							MString stringDefault( shaderInfo.getArgStringDefault( i, 0 ) );
							if( stringPlugVal == stringDefault )
							{
								skipToken = true;
							}
							else
							{
								MString stringVal( parseString( stringPlugVal ) );
								LIQDEBUGPRINTF("[liqShader::liqShader] parsed string for param %s = %s \n", paramName.asChar(), stringVal.asChar() );
								tokenPointerArray.rbegin()->set( paramName.asChar(), rString );
								tokenPointerArray.rbegin()->setTokenString( 0, stringVal.asChar() );
							}
						}
					}
					else
					{
						skipToken = true;
					}
					break;
				}
				case SHADER_TYPE_SCALAR:
				{
					MPlug floatPlug( shaderNode.findPlug( paramName, &status ) );
					if ( MS::kSuccess == status )
					{
						if( arraySize == 0 )
						{
							skipToken = true;
							liquidMessage2(messageWarning, "[liqShader] warning undefined float array size, not yet implemented ....\n");
						}
						else if( arraySize > 0 )
						{
							bool isArrayAttr( floatPlug.isArray( &status ) );
							if ( isArrayAttr )
							{
								// philippe : new way to store float arrays as multi attr
								MPlug plugObj;
								tokenPointerArray.rbegin()->set( paramName.asChar(), rFloat, false, true, arraySize );
								//tokenPointerArray.rbegin()->set( paramName.asChar(), rFloat, 1, arraySize, true );
								for( unsigned int kk( 0 ); kk < (unsigned int)arraySize; kk++ )
								{
									plugObj = floatPlug.elementByLogicalIndex( kk, &status );
									if ( MS::kSuccess == status )
									{
										float x;
										plugObj.getValue( x );
										tokenPointerArray.rbegin()->setTokenFloat( kk, x );
									}
								}
							}
						}
						else if( arraySize == -1 )
						{
							float floatPlugVal;
							floatPlug.getValue( floatPlugVal );
							tokenPointerArray.rbegin()->set( paramName.asChar(), rFloat );
							tokenPointerArray.rbegin()->setTokenFloat( 0, floatPlugVal );
						}
					}
					else
					{
						skipToken = true;
					}
					break;
				}
				case SHADER_TYPE_COLOR:
				case SHADER_TYPE_POINT:
				case SHADER_TYPE_VECTOR:
				case SHADER_TYPE_NORMAL:
				{
					ParameterType parameterType;
					if( shaderType==SHADER_TYPE_COLOR )
					{
						parameterType = rColor;
					}
					else if(shaderType==SHADER_TYPE_POINT)
					{
						parameterType = rPoint;
					}
					else if(shaderType==SHADER_TYPE_VECTOR)
					{
						parameterType = rVector;
					}
					else if(shaderType==SHADER_TYPE_NORMAL)
					{
						parameterType = rNormal;
					}
					if( arraySize==0 )
					{
						liquidMessage2(messageWarning, "[liqShader] warning undefined float[3] array size, not yet implemented ....\n");
						skipToken = true;
					}
					else if ( arraySize > 0 )
					{
						status = liqShaderParseVectorArrayAttr( shaderNode, paramName.asChar(), parameterType, arraySize );
						if( status != MS::kSuccess )
						{
							skipToken = true;
							liquidMessage2(messageError, "[liqShader] error while building float[3] array param %s on %s ...\n", paramName.asChar(), shaderNode.name().asChar() );
						}
					}
					else
					{
						status = liqShaderParseVectorAttr( shaderNode, paramName.asChar(), parameterType );
						if( status != MS::kSuccess )
						{
							skipToken = true;
							liquidMessage2(messageError, "[liqShader] error while building float[3] param %s on %s ...\n", paramName.asChar(), shaderNode.name().asChar() );
						}
					}
					break;
				}
				case SHADER_TYPE_MATRIX:
				{
					//liquidMessage2(messageInfo,  "[liqShader]  %s.%s arraySize=%d", shaderNode.name().asChar(), paramName.asChar(), arraySize );
					if ( arraySize > 0 )
					{
 						liquidMessage2(messageError, "[liqShader] matrix array is not supported. %s.%s ...\n", shaderNode.name().asChar(), paramName.asChar() );
					} else {
						status = liqShaderParseMatrixAttr( shaderNode, paramName.asChar(), rMatrix );
						if( status != MS::kSuccess )
						{
							skipToken = true;
							liquidMessage2(messageError, "[liqShader] error while building matrix. %s.%s ...\n", shaderNode.name().asChar() , paramName.asChar());
						}
					}
					break;
				}
				case SHADER_TYPE_SHADER:
				{
					MPlug coShaderPlug = shaderNode.findPlug( paramName, &status );
					if ( MS::kSuccess == status )
					{
						// undefined array size : set array size to nbConnections
						if( arraySize==0 )
						{
							MPlug plugObj;
							unsigned int numConnectedElements = coShaderPlug.numConnectedElements();
							if( numConnectedElements == 0 )
							{
								skipToken = true;
							}
							else
							{
								arraySize = numConnectedElements;
							}
						}
						if ( arraySize > 0 )
						{
							unsigned int i;
							// Gestion en mode shader (message connection) 
							unsigned int numConnectedElements = coShaderPlug.numConnectedElements();
							tokenPointerArray.rbegin()->set( paramName.asChar(), rString, numConnectedElements );
							for(i=0; i<numConnectedElements; i++)
							{
								MPlug connectedPlug = coShaderPlug.connectionByPhysicalIndex(i);
								bool asSrc = 0;
								bool asDst = 1;
								MPlugArray connectedPlugArray;
								connectedPlug.connectedTo( connectedPlugArray, asDst, asSrc );
								MObject coshader = connectedPlugArray[0].node();
								appendCoShader(coshader, connectedPlugArray[0]);
								MString coShaderId = liqShaderFactory::instance().getShaderId(coshader);
								tokenPointerArray.rbegin()->setTokenString( i, coShaderId.asChar() );
							}

							// Gestion en mode string
							//bool isArrayAttr( coShaderPlug.isArray( &status ) );
							//if ( isArrayAttr )
							//{
							//	MPlug plugObj;
							//	tokenPointerArray.rbegin()->set( paramName.asChar(), rShader, arraySize );
							//	for( unsigned int kk( 0 ); kk < (unsigned int)arraySize; kk++ )
							//	{
							//		plugObj = coShaderPlug.elementByLogicalIndex( kk, &status );
							//		printf("          value %d : ", kk);

							//		if ( MS::kSuccess == status )
							//		{
							//			MString stringPlugVal;
							//			plugObj.getValue( stringPlugVal );
							//			MString stringVal = parseString( stringPlugVal );
							//			tokenPointerArray.rbegin()->setTokenString( kk, stringVal.asChar() );
							//			printf(" %s ", stringVal.asChar());
							//		}
							//		else
							//		{
							//			printf("[liqShader] error while building shader param %d : %s \n", kk, coShaderPlug.name().asChar() );
							//		}
							//		printf("\n");
							//	}
							//	//tokenPointerArray.push_back( liqTokenPointer() );
							//}
							//else
							//{
							//	printf("[liqShader] error while building param %s assumed as an array but wasn't...\n", coShaderPlug.name().asChar() );
							//}
						}
						else if ( arraySize == -1 )
						{
							// Gestion en mode shader (message connection) 
							MPlugArray connectionArray;
							bool asSrc = 0;
							bool asDst = 1;
							coShaderPlug.connectedTo(connectionArray, asDst, asSrc);
							if( connectionArray.length() == 0 )
							{
								skipToken = true;
							}
							else
							{
								MPlug connectedPlug = connectionArray[0];
								MObject coshader = connectedPlug.node();
								appendCoShader(coshader, coShaderPlug);
								MString coShaderId = liqShaderFactory::instance().getShaderId(coshader);
								tokenPointerArray.rbegin()->set( paramName.asChar(), rString );
								tokenPointerArray.rbegin()->setTokenString( 0, coShaderId.asChar() );
							}

							// Gestion en mode string
							
							//MString stringPlugVal;
							//coShaderPlug.getValue( stringPlugVal );
							//MString stringDefault( shaderInfo.getArgStringDefault( i, 0 ) );
							//if ( stringPlugVal == stringDefault )
							//{
							//	skipToken = true;
							//	printf("          value : default => skipping \n");
							//}
							//else
							//{
							//	MString stringVal( parseString( stringPlugVal ) );
							//	LIQDEBUGPRINTF("[liqShader::liqShader] parsed string for param %s = %s \n", paramName.asChar(), stringVal.asChar() );
							//	tokenPointerArray.rbegin()->set( shaderInfo.getArgName( i ).asChar(), rString );
							//	tokenPointerArray.rbegin()->setTokenString( 0, stringVal.asChar() );
							//	printf("          value : %s \n", stringVal.asChar());
							//}
							
						}
					}
					break;
				}
				case SHADER_TYPE_UNKNOWN :
				default:
					liquidMessage( "Unknown shader type", messageError );
					skipToken = true;
					break;
			}
			if( !skipToken )
			{
				// set token type
				switch ( shaderDetail )
				{
					case SHADER_DETAIL_UNIFORM:
					{
						tokenPointerArray.rbegin()->setDetailType( rUniform );
						break;
					}
					case SHADER_DETAIL_VARYING:
					{
						tokenPointerArray.rbegin()->setDetailType( rVarying);
						break;
					}
					case SHADER_DETAIL_UNKNOWN:
						tokenPointerArray.rbegin()->setDetailType( rUniform);
						break;
				}
				// create next token
				tokenPointerArray.push_back( liqTokenPointer() );
			}
			else
			{
				// skip parameter : parameter will not be written inside rib
			}
		}
	}
	shaderInfo.resetIt();
}


liqShader::~liqShader()
{
}


void liqShader::appendCoShader(MObject coshader, MPlug plug)
{
	// test if it's really a co-shader
	int isLiquidShader = 0;
	MFn::Type objectType = coshader.apiType();
	if( objectType == MFn::kPluginDependNode )
	{
		MFnDependencyNode fnObject(coshader);
		MTypeId depNodeId = fnObject.typeId();
		//liquidMessage2(messageInfo, "liqSurfaceNodeId=%d  liqDisplacementNodeId=%d  liqVolumeNodeId=%d  liqCoShaderNodeId=%d\n", liqSurfaceNodeId, liqDisplacementNodeId, liqVolumeNodeId, liqCoShaderNodeId);
		if( depNodeId==liqSurfaceNodeId || depNodeId==liqDisplacementNodeId || depNodeId==liqVolumeNodeId || depNodeId==liqCoShaderNodeId )
		{
			isLiquidShader = 1;
		}
	}
	if( isLiquidShader )
	{
		MFnDependencyNode fnObject(coshader);
		m_coShaderArray.push_back(coshader);
	}
	else
	{
		liquidMessage2(messageError, "[liqShader::appendCoShader] Error unsupported connection in plug '%s', abort co-shading for this plug.\n", plug.name().asChar());
	}
}


MStatus liqShader::liqShaderParseVectorAttr ( const MFnDependencyNode& shaderNode, const string& argName, ParameterType pType )
{
	MStatus status( MS::kSuccess );

	MPlug triplePlug( shaderNode.findPlug( argName.c_str(), &status ) );

	if ( MS::kSuccess == status )
	{
		float x, y, z;
		tokenPointerArray.rbegin()->set( argName.c_str(), pType );
		triplePlug.child( 0 ).getValue( x );
		triplePlug.child( 1 ).getValue( y );
		triplePlug.child( 2 ).getValue( z );
		tokenPointerArray.rbegin()->setTokenFloat( 0, x, y, z );
		//tokenPointerArray.push_back( liqTokenPointer() );
	}
  return status;
}

// philippe : multi attr support
MStatus liqShader::liqShaderParseVectorArrayAttr ( const MFnDependencyNode& shaderNode, const string& argName, ParameterType pType, unsigned int arraySize )
{
  MStatus status( MS::kSuccess );

  MPlug triplePlug( shaderNode.findPlug( argName.c_str(), true, &status ) );

  if ( MS::kSuccess == status ) {
    tokenPointerArray.rbegin()->set( argName, pType, false, true, arraySize );
    for( unsigned int kk( 0 ); kk < arraySize; kk++ ) {
      MPlug argNameElement( triplePlug.elementByLogicalIndex( kk ) );

      if ( MS::kSuccess == status ) {
        float x, y, z;
        argNameElement.child( 0 ).getValue( x );
        argNameElement.child( 1 ).getValue( y );
        argNameElement.child( 2 ).getValue( z );
        tokenPointerArray.rbegin()->setTokenFloat( kk, x, y, z );
      }
    }
    //tokenPointerArray.push_back( liqTokenPointer() );
  }

  return status;
}


void liqShader::write(bool shortShaderNames, unsigned int indentLevel)
{
	MFnDependencyNode node(m_mObject);
	if( hasErrors )
	{
		liquidMessage2(messageError,"[liqShader::write] Erros occured while initializing shader '%s', won't export shader", node.name().asChar());
		return;
	}
	// write co-shaders before
	unsigned int i; 
	for(i=0; i<m_coShaderArray.size(); i++)
	{
		liqShader &coShader = liqShaderFactory::instance().getShader(m_coShaderArray[i]);
		if( coShader.hasErrors )
		{
			char errorMsg[512];
			sprintf(errorMsg, "[liqShader::write] While initializing coShader for '%s', node couldn't be exported", coShader.name.c_str());
			liquidMessage( errorMsg, messageError );
		}
		else
		{
			coShader.writeAsCoShader(shortShaderNames, indentLevel);
		}
	}
	// write shader
	scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
	scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
	assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );
	char* shaderFileName = shortShaderNames ? basename( const_cast<char *>(file.c_str())) : const_cast<char *>(file.c_str());
	if( shaderSpace != "" )
	{
		RiTransformBegin();
		RiCoordSysTransform( ( RtString )shaderSpace.asChar() );
	}
	// output shader
	// its one less as the tokenPointerArray has a preset size of 1 not 0
	int shaderParamCount = tokenPointerArray.size() - 1;
	switch( shader_type )
	{
    case SHADER_TYPE_LIGHT :
    {  
      outputIndentation(indentLevel);
		RtLightHandle ret = RiLightSourceV( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
 #ifdef RIBLIB_AQSIS
		shaderHandler.set( reinterpret_cast<ptrdiff_t>(static_cast<RtLightHandle>(ret)) );
#else
		shaderHandler.set( ret );
#endif
	  } break;
	    
	case SHADER_TYPE_SURFACE :
		outputIndentation(indentLevel);
		RiSurfaceV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
		break;
	case SHADER_TYPE_DISPLACEMENT :
		outputIndentation(indentLevel);
		RiDisplacementV( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
		break;
	case SHADER_TYPE_VOLUME :
		outputIndentation(indentLevel);
		RiAtmosphereV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
		break;
	default :
		char errorMsg[512];
		sprintf(errorMsg, "[liqShader::write] Unknown shader type for %s shader_type=%d", name.c_str(), shader_type);
		liquidMessage( errorMsg, messageError );
		break;
	}
	if( shaderSpace != "" )
	{
		RiTransformEnd();
	}
}


void liqShader::writeAsCoShader(bool shortShaderNames, unsigned int indentLevel)
{
	MFnDependencyNode node(m_mObject);
	if( hasErrors )
	{
		liquidMessage2(messageError, "[liqShader::write] Erros occured while initializing shader '%s', won't export shader", node.name().asChar());
		return;
	}
	// write up co-shaders before
	unsigned int i; 
	for(i=0; i<m_coShaderArray.size(); i++)
	{
		//liqShader coShader(m_coShaderArray[i]);
		liqShader &coShader = liqShaderFactory::instance().getShader(m_coShaderArray[i]);
		coShader.writeAsCoShader(shortShaderNames, indentLevel);
	}
	// write co-shader
	scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
	scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
	assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );
	char* shaderFileName = shortShaderNames ? basename( const_cast<char *>(file.c_str())) : const_cast<char *>(file.c_str());
	if( shaderSpace != "" )
	{
		RiTransformBegin();
		RiCoordSysTransform( ( RtString )shaderSpace.asChar() );
	}
	// output shader
	// its one less as the tokenPointerArray has a preset size of 1 not 0
	int shaderParamCount = tokenPointerArray.size() - 1;
	char *shaderHandlerPtr = const_cast<char*>(shaderHandler.asChar());
	switch( shader_type )
	{
	case SHADER_TYPE_SHADER :
	case SHADER_TYPE_SURFACE :
	case SHADER_TYPE_DISPLACEMENT :
	case SHADER_TYPE_VOLUME :
		outputIndentation(indentLevel);
		RiShaderV(shaderFileName, shaderHandlerPtr, shaderParamCount, tokenArray.get(), pointerArray.get());
		break;
	default :
		char errorMsg[512];
		sprintf(errorMsg, "[liqShader::writeAsCoShader] Unknown shader type for %s shader_type=%d (%s)", name.c_str(), shader_type, liqGetSloInfo::getTypeStr(shader_type).asChar());
		liquidMessage( errorMsg, messageError );
		break;
	}
	if( shaderSpace != "" )
	{
		RiTransformEnd();
	}
}


void liqShader::outputIndentation(unsigned int indentLevel)
{
	for(unsigned int i=0; i<indentLevel; ++i)
	{
		RiArchiveRecord(RI_VERBATIM, "\t");
	}
}

MStatus liqShader::liqShaderParseMatrixAttr ( const MFnDependencyNode& shaderNode, const string& argName, ParameterType pType )
{
	MStatus status( MS::kSuccess );

	MPlug matrixPlug( shaderNode.findPlug( argName.c_str(), &status ) );

	if ( MS::kSuccess == status )
	{
 		tokenPointerArray.rbegin()->set( argName.c_str(), pType );
		
		RtFloat matrixBuff[16];

		//get matrix value
		MObject oMatrix;
		matrixPlug.getValue(oMatrix);
		MFnMatrixData fndMatrix(oMatrix, &status);
		LIQCHECKSTATUS(status,"liqShader::liqShaderParseMatrixAttr(...) fndMatrix");
		MMatrix matrix(fndMatrix.matrix(&status));
		LIQCHECKSTATUS(status,"liqShader::liqShaderParseMatrixAttr(...) mmatrix");
		RtFloat mmatrixBuff[4][4];
		matrix.get(mmatrixBuff);
		matrixBuff[0 ] = mmatrixBuff[0][0];  matrixBuff[1 ] = mmatrixBuff[0][1];  matrixBuff[2 ] = mmatrixBuff[0][2];  matrixBuff[3 ] = mmatrixBuff[0][3];
		matrixBuff[4 ] = mmatrixBuff[1][0];  matrixBuff[5 ] = mmatrixBuff[1][1];  matrixBuff[6 ] = mmatrixBuff[1][2];  matrixBuff[7 ] = mmatrixBuff[1][3];
		matrixBuff[8 ] = mmatrixBuff[2][0];  matrixBuff[9 ] = mmatrixBuff[2][1];  matrixBuff[10] = mmatrixBuff[2][2];  matrixBuff[11] = mmatrixBuff[2][3];
		matrixBuff[12] = mmatrixBuff[3][0];  matrixBuff[13] = mmatrixBuff[3][1];  matrixBuff[14] = mmatrixBuff[3][2];  matrixBuff[15] = mmatrixBuff[3][3];
      
		//you can alose get the matrix value by mel
// 		MDoubleArray matrix;
// 		MString cmd;
// 		cmd += "getAttr "+shaderNode.name()+"."+(MString)(argName.c_str());
// 		MGlobal::executeCommand(cmd, matrix);
// 		liquidMessage2(messageInfo, "m[][]={%f, %f, %f, %f, ...}",matrix[0] , matrix[1], matrix[2], matrix[3]);
//		matrix.get(matrixBuff);

		tokenPointerArray.rbegin()->setTokenFloats( matrixBuff );			
		//tokenPointerArray.push_back( liqTokenPointer() );
	}
	return status;
}
//
void liqShader::buildJobs()
{
	scanExpressions(*this);
}
// check shaders to see if "string" parameters are expression
// replace expression with calculated values
void liqShader::scanExpressions( liqShader & currentShader )
{
	for ( vector< liqTokenPointer >::iterator it( currentShader.tokenPointerArray.begin() ); 
		it != currentShader.tokenPointerArray.end(); 
		it++ ) 
	{
		if( it->getParameterType() == rString )
			processExpression( &( *it ) );
	}
}
//
void liqShader::processExpression( liqTokenPointer *token, liqRibLightData *light )
{
	if( token != NULL ) 
	{
		string strValue( token->getTokenString() );
		LIQDEBUGPRINTF( "-> Expression:(%s)\n", token->getTokenName().c_str() );
		// NOTE:
		// For convenience, we use the image path instead of [MakeTexture ...],
		// e.g. we use c:/test.bmp for  [MakeTexture c:/test.bmp]
		if( !IS_EXPRESSION(strValue.c_str()) )
		{
			LIQDEBUGPRINTF("texturePathPoint=%s, strValue=%s\n", strValue.c_str(), strValue.c_str());
			strValue = "[MakeTexture "+strValue+"]";
		}

		liqExpression expr( strValue );
		if( expr.type != exp_None && expr.isValid ) 
		{ // we've got expression here
			expr.CalcValue(); // calculate value;
			switch ( expr.type ) 
			{
			case exp_CoordSys:
				LIQDEBUGPRINTF( "-> CoordSys Expression: %s\n", expr.GetValue().asChar() );
				token->setTokenString( 0, expr.GetValue().asChar() );
				break;

			case exp_MakeTexture:
				{
					token->setTokenString( 0, expr.GetValue().asChar() );
					if( !expr.destExists || !expr.destIsNewer ) {
						LIQDEBUGPRINTF( "-> Making Texture: %s\n", liqglo.liquidRenderer.textureMaker.asChar() );
						LIQDEBUGPRINTF( "-> MakeTexture Command: %s\n", expr.GetCmd().asChar() );

						structJob thisJob;
						thisJob.pass = rpMakeTexture;
						thisJob.renderName = liqglo.liquidRenderer.textureMaker;
						thisJob.ribFileName = expr.GetCmd();
						thisJob.imageName = expr.GetValue(); // destination file name

						//skip
						std::size_t loc = strValue.find_last_of('.');
						if( loc == std::string::npos )
							liquidMessage2(messageError,"%s has no extention!", strValue.c_str());
						string extention;
						if( *(strValue.rbegin())==']' ){//if the strValue end with ']', extention should exclude the ']'
							extention = strValue.substr(loc+1, strValue.size()-loc-2);
							cout << "extention = "<<extention<<endl;
						}else{
							extention = strValue.substr(loc+1);
						}
						thisJob.skip = ("tex"==extention);

						vector<structJob>::iterator iter = liqRibTranslator::getInstancePtr()->txtList.begin();
						while ( iter != liqRibTranslator::getInstancePtr()->txtList.end() ) {
							if( iter->imageName == thisJob.imageName )
								break; // already have this job
							++iter;
						}
						liqRibTranslator::getInstancePtr()->txtList.push_back( thisJob );

					}
				}
				break;

			case exp_ReflectMap:
				LIQDEBUGPRINTF( "-> ReflectMap Expression: %s\n", expr.GetValue().asChar());
				token->setTokenString( 0, expr.GetValue().asChar() );
				break;

			case exp_Shadow:
			case exp_PointShadow:
				{
					MString shadowName = liqglo.liqglo_textureDir + light->autoShadowName();
					token->setTokenString( 0, shadowName.asChar() );
				}
				break;

			case exp_EnvMap:
			case exp_CubeEnvMap:
			case exp_None:
			default:
				break;
			}
		}
	}
}
