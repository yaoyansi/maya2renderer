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
#ifndef liqTokenPointer_H
#define liqTokenPointer_H

#include <string>
#include <vector>
#include <boost/shared_array.hpp>
//extern "C" {
#include "ri_interface.h"
//}

// token/pointer pairs structure

enum ParameterType 
{
  rFloat  = 0,
  rPoint  = 1,
  rVector = 2,
  rNormal = 3,
  rColor  = 4,
  rString = 5,
  rHpoint = 6,
  rMatrix = 7,
  rShader = 8
};

enum DetailType 
{
  rUndefined    = -1,
  rUniform      =  0,
  rVarying      =  1,
  rVertex       =  2,
  rConstant	    =  3,
  rFaceVarying  =  4,
  rFaceVertex   =  5
};

class liqTokenPointer
{
  public:
    liqTokenPointer();
    liqTokenPointer(const liqTokenPointer& src);
    liqTokenPointer& operator=( const liqTokenPointer& src);
	                 operator bool() const;
    virtual ~liqTokenPointer();

    void           setTokenName( const std::string& name );
    bool           set( const std::string& name, ParameterType ptype );
    bool           set( const std::string& name, ParameterType ptype, unsigned int arraySize );
    bool           set( const std::string& name, ParameterType ptype, unsigned int arraySize, unsigned int uArraySize );
    // Deprecated: use one of the above three set() functions instead!
    bool           set( const std::string& name, ParameterType ptype, bool asArray, bool asUArray, unsigned int arraySize );
    // -----------
    int            reserve( unsigned int size );
    void           setDetailType( DetailType dType );
    void           setTokenFloat( unsigned int i, RtFloat val );
    void           setTokenFloat( unsigned int i, unsigned int uIndex, RtFloat val );
    void           setTokenFloat( unsigned int i, RtFloat x, RtFloat y , RtFloat z );
    void           setTokenFloat( unsigned int i, RtFloat x, RtFloat y , RtFloat z, RtFloat w );
	void           setTokenFloats( const boost::shared_array< RtFloat > floatVals ); // Warning! This method assumes ownership of the pointer is transferred to the TokenPointer!!!
    void           setTokenFloats( const RtFloat* floatVals ); // Use this one to copy the data
    void           setTokenString( unsigned int i, const std::string& str );

    const std::string&						getDetailedTokenName();
    DetailType								getDetailType() const;

    const RtFloat*							getTokenFloatArray() const;
	const boost::shared_array< RtFloat >	getTokenFloatSharedArray() const;
    std::string								getTokenString() const;
	std::string								getTokenName() const;

    ParameterType							getParameterType() const;

    const RtPointer							getRtPointer();
    std::string								getRiDeclare() const;

    bool           empty() const;
    bool           isBasicST() const;
    void           resetTokenString();
    void           reset();

    typedef std::vector< liqTokenPointer > array;
  private:
	boost::shared_array< RtFloat >	m_tokenFloats;
    std::vector< std::string >		m_tokenString;
	boost::shared_array< RtString > m_tokenStringArray; // Holds pointers for getRtPointer();
    ParameterType	m_pType;
    DetailType		m_dType;
    std::string		m_tokenName;
    std::string		detailedTokenName; // This needs to be a member or else the getTokenArrays...() stuff fails as it uses c_str() on a temporary string.
    unsigned m_arraySize;
    unsigned m_uArraySize;
    unsigned m_eltSize;
    bool m_isArray;
    bool m_isUArray;
    bool m_isString;
    bool m_isFull;
    static const std::string detailType[];
    int m_stringSize;
    int m_tokenSize;
};


#endif //liquidTokenPointer_H
