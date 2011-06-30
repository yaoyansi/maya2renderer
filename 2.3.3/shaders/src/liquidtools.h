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
** Contributor(s): Moritz Moeller
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
**
*/

/* ______________________________________________________________________
**
** liquidtools.h Source
** ______________________________________________________________________
*/

uniform string liqPass() {
  uniform string pass = "unknown";
  option( "user:pass", pass );
  return pass;
}

float liqReceivesShadows() {
  uniform float receive = 1;
  attribute( "user:receivesshadows", receive );
  return clamp( receive, 0, 1 );
}

uniform string liqSelfSubset() {
  uniform string subset = "";
  attribute( "identifier:name", subset )
  return subset;
}

// Returns the adjusted number of samples based on the global user settings
uniform float liqGlobalRayTraceSamples( uniform float samples ) {
  uniform float usersamples;

  uniform float breadthscale;
  if( option( "user:tracebreadthfactor", breadthscale ) == 1 ) {
    usersamples = ceil( samples * breadthscale );
  } else {
    usersamples = samples;
  }

  uniform float depthscale;
  if( ( option( "user:tracedepthfactor", depthscale ) == 1 ) && ( depthscale > 1 ) ) {
    uniform float raydepth;
    rayinfo( "depth", raydepth );
    if( depth > 0 ) {
      depthscaler = pow( factor, depth );
      usersamples = ceil( factor * depthscale );
    }
  }
  
  return usersamples;
}


#define LIQ_BAKE_INIT                                                         \
  float _liqBakePass = liqGetPass() == "bake";                                \
  string _liqObjectName = "";                                                 \
  attribute( "identifier:name", _liqObjName )


#define LIQ_BAKE_OR_LOOKUP( bakename, s, t, func, dest ) {                    \
  if( _liqBakePass != 0 ) {                                                   \
  dest = func( s,t );                                                       \
  string bakefilename = concat( objname, ".", bakename, ".bake" );          \
  bake( bakefilename, s, t, dest );                                         \
  } else {                                                                    \
  string filename = concat( objname, ".", bakename, ".tx" );                \
  dest = texture( filename, s, t );                                         \
  }                                                                           \
}


#define LIQ_BAKE( bakename, s, t, dest ) {                                    \
  if( _liqBakePass != 0 ) {                                                   \
  string bakefilename = concat( objname, ".", bakename, ".bake" );          \
  bake( bakefilename, s, t, dest );                                         \
  }                                                                           \
}
