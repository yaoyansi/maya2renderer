
#include <liqFrameScriptMgr.h>

#include <sstream>
#include <liqRenderScript.h>
#include <liqGlobalVariable.h>

tFrameScriptJobMgr::tFrameScriptJobMgr(liqRenderScript::Job& script)
:m_frameScriptJob(script)
{

}
//
tFrameScriptJobMgr::~tFrameScriptJobMgr()
{

}
//
void tFrameScriptJobMgr::setCommonParameters(const std::string &title )
{ 
	CM_TRACE_FUNC("tFrameScriptJobMgr::setCommonParameters("<<title<<")");

	m_frameScriptJob.title = title;
}
//
void tFrameScriptJobMgr::addInstanceJob(  const bool isInstance,
					const std::string &title
					)
{ 
	CM_TRACE_FUNC("tFrameScriptJobMgr::addInstanceJob("<<isInstance<<","<<title<<")");

	liqRenderScript::Job instanceJob__;
	instanceJob__.isInstance = isInstance;
	instanceJob__.title = title;
	m_frameScriptJob.childJobs.push_back(instanceJob__);
}
//
// void tFrameScriptJobMgr::addJob(
// 						   const std::string &title, 
// 						   const std::string &command, const bool remote
// 						   )
// {
// 	liqRenderScript::Job job;
// 	job.title = title;
// 	job.commands.push_back( liqRenderScript::Cmd( command, remote ) );
// 	m_frameScriptJob.addJob( job );
// }

void tFrameScriptJobMgr::makeTexture(
	std::vector<structJob>  &txtList___,
	bool &alf_textures__,
	bool &alf_shadows__,
	bool &alf_refmaps__
)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeTexture(txtList___,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<")");

	if( txtList___.size() ) 
	{
		liqRenderScript::Job textureJob;
		makeTexturePass(txtList___, textureJob, 
			alf_textures__, alf_shadows__, alf_refmaps__ 
			);
		m_frameScriptJob.childJobs.push_back( textureJob );
	}//if( txtList.size() )
}
//
void tFrameScriptJobMgr::makeTexturePass(
									   std::vector<structJob> &txtList__, 
									   liqRenderScript::Job &textureJob__,
									   bool &alf_textures__,
									   bool &alf_shadows__,
									   bool &alf_refmaps__
									   )
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeTexturePass(txtList___,textureJob__,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<")");

	std::vector<structJob>::iterator iter = txtList__.begin();

	alf_textures__ = true;

	std::stringstream ts;
	ts << "Textures." << liqglo.liqglo_lframe;
	textureJob__.title = ts.str();

	while ( iter != txtList__.end() ) 
	{
		liqRenderScript::Job textureSubtask;
		std::stringstream ts;
		ts << textureJob__.title << " " << iter->imageName.asChar();
		textureSubtask.title = ts.str();
// 		if( m_deferredGen ) {
// 
// 		}
		std::stringstream ss;
		ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
		liqRenderScript::Cmd cmd( ss.str(), ( liqglo.remoteRender && !liqglo.useNetRman ) );

		if( liqglo.m_alfredExpand ) 
			cmd.alfredExpand = true;

		cmd.alfredServices = liqglo.m_alfredServices.asChar();
		cmd.alfredTags     = liqglo.m_alfredTags.asChar();
		textureSubtask.commands.push_back( cmd );
		textureSubtask.chaserCommand = ( std::string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
		++iter;
		textureJob__.childJobs.push_back( textureSubtask );
	}
}
//
void tFrameScriptJobMgr::makeShadow(
				std::vector<structJob> &shadowList__,
				bool &alf_textures__,
				bool &alf_shadows__,
				bool &alf_refmaps__,
				const int currentBlock__
				)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeShadow(shadowList__,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<","<<currentBlock__<<")");

	const MString framePreCommand(parseString( liqglo.m_preCommand, false));
	const MString frameRenderCommand( parseString( liqglo.liquidRenderer.renderCommand + " " + liqglo.liquidRenderer.renderCmdFlags, false ));

	if( shadowList__.size() ) 
	{
		liqRenderScript::Job shadowJob;
		makeShadowPass(shadowList__, shadowJob, 
			alf_textures__, alf_shadows__, alf_refmaps__, 
			framePreCommand, frameRenderCommand, 
			currentBlock__
			);
		m_frameScriptJob.childJobs.push_back( shadowJob );
	}//if( shadowList.size() )
}
//
void tFrameScriptJobMgr::makeShadowPass(
										std::vector<structJob> &shadowList__, 
										liqRenderScript::Job &shadowJob__,
										bool &alf_textures__,
										bool &alf_shadows__,
										bool &alf_refmaps__,
										const MString &framePreCommand__,
										const MString &frameRenderCommand__,
										const int currentBlock__
										)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeShadowPass(shadowList__,shadowJob__,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<","
		<<framePreCommand__<<", "<<frameRenderCommand__<<", "<<currentBlock__<<")");

	std::vector< structJob >::iterator iter = shadowList__.begin();

	alf_shadows__ = true;

	std::stringstream ts;
	ts << "Shadows." << liqglo.liqglo_lframe;
	shadowJob__.title = ts.str();
	while ( iter != shadowList__.end() ) 
	{
		alf_shadows__ = true;
		liqRenderScript::Job shadowSubtask;
		shadowSubtask.title = iter->name.asChar();
		if( alf_textures__ ) 
		{
			std::stringstream ss;
			ss << "Textures." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			shadowSubtask.childJobs.push_back(instanceJob);
		}
		if( liqglo.m_deferredGen ) 
		{
			std::stringstream ss;
			ss << liquidTransGetSceneName().asChar() << "FrameRIBGEN" << currentBlock__;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			shadowSubtask.childJobs.push_back(instanceJob);
		}
		std::stringstream ss;
		if( liqglo.useNetRman ) 
		{
#ifdef _WIN32
			ss << framePreCommand__.asChar() << " netrender %H -Progress \"" << iter->ribFileName.asChar() << "\"";
#else
			ss << framePreCommand__.asChar() << " netrender %H -Progress " << iter->ribFileName.asChar();
#endif
		} else {
#ifdef _WIN32
			ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " \"" << iter->ribFileName.asChar() << "\"";
#else
			ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " " << iter->ribFileName.asChar();
#endif
		}
		liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
		if( liqglo.m_alfredExpand ) 
			cmd.alfredExpand = true;

		cmd.alfredServices = liqglo.m_alfredServices.asChar();
		cmd.alfredTags     = liqglo.m_alfredTags.asChar();
		shadowSubtask.commands.push_back(cmd);

 		if(liqglo.cleanRib)  
 		{
 			std::stringstream ss;
 #ifdef _WIN32
 			ss << framePreCommand__.asChar() << " " << RM_CMD << " \"" << iter->ribFileName.asChar() << "\"";
 #else
 			ss << framePreCommand__.asChar() << " " << RM_CMD << " " << iter->ribFileName.asChar();
 #endif
 
 			shadowSubtask.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );
 		}
		shadowSubtask.chaserCommand = ( std::string( "sho \"" ) + iter->imageName.asChar() + "\"" );
		++iter;
		if( !liqglo.m_alfShadowRibGen && !liqglo.fullShadowRib ) 
			liqglo.m_alfShadowRibGen = true;
		shadowJob__.childJobs.push_back( shadowSubtask );
	}
}
//
void tFrameScriptJobMgr::makeReflection(
					std::vector<structJob> &refList__,
					bool &alf_textures__,
					bool &alf_shadows__,
					bool &alf_refmaps__
					)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeReflection(refList__,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<")");

	if( refList__.size() ) 
	{	
		liqRenderScript::Job reflectJob;
		makeReflectionPass(refList__, reflectJob, 
			alf_textures__, alf_shadows__, alf_refmaps__
			);
		m_frameScriptJob.childJobs.push_back( reflectJob );
	}
}
//
void tFrameScriptJobMgr::makeReflectionPass(
	std::vector<structJob> &refList__, 
	liqRenderScript::Job &reflectJob__,
	bool &alf_textures__,
	bool &alf_shadows__,
	bool &alf_refmaps__
	)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::makeReflectionPass(refList__,reflectJob__,"<<alf_textures__<<","<<alf_shadows__<<","<<alf_refmaps__<<")");

	LIQDEBUGPRINTF( "-> Generating job for ReflectionMap pass\n" );
	std::vector<structJob>::iterator iter = refList__.begin();

	alf_refmaps__ = true;

	std::stringstream ts;
	ts << "Reflections." << liqglo.liqglo_lframe;
	reflectJob__.title = ts.str();

	while ( iter != refList__.end() ) 
	{
		liqRenderScript::Job reflectSubtask;
		std::stringstream ts;
		ts << reflectJob__.title << " " << iter->imageName.asChar();
		reflectSubtask.title = ts.str();
		if( liqglo.m_deferredGen ) {

		}
		if( alf_textures__ ) 
		{
			std::stringstream ss;
			ss << "Textures." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			reflectJob__.childJobs.push_back( instanceJob );
		}
		if( alf_shadows__ ) 
		{
			std::stringstream ss;
			ss << "Shadows." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			reflectJob__.childJobs.push_back( instanceJob );
		}

		std::stringstream ss;
		ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
		liqRenderScript::Cmd cmd( ss.str(), (liqglo.remoteRender && !liqglo.useNetRman) );

		if( liqglo.m_alfredExpand ) 
			cmd.alfredExpand = true;

		cmd.alfredServices = liqglo.m_alfredServices.asChar();
		cmd.alfredTags     = liqglo.m_alfredTags.asChar();
		reflectSubtask.commands.push_back( cmd );
		reflectSubtask.chaserCommand = ( std::string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
		++iter;
		reflectJob__.childJobs.push_back( reflectSubtask );
	}

}
//

void tFrameScriptJobMgr::try_addPreFrameCommand(const MString &framePreFrameCommand__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::try_addPreFrameCommand("<<framePreFrameCommand__<<")");

	if( framePreFrameCommand__ != MString("") ) 
	{
		liqRenderScript::Cmd cmd(framePreFrameCommand__.asChar(), (liqglo.remoteRender && !liqglo.useNetRman));
		cmd.alfredServices = liqglo.m_alfredServices.asChar();
		cmd.alfredTags     = liqglo.m_alfredTags.asChar();
		m_frameScriptJob.commands.push_back(cmd);
	}
}
//
void tFrameScriptJobMgr::try_addPostFrameCommand(const MString &framePostFrameCommand__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::try_addPostFrameCommand("<<framePostFrameCommand__<<")");

	if( framePostFrameCommand__ != MString("") ) 
	{
		liqRenderScript::Cmd cmd(framePostFrameCommand__.asChar(), (liqglo.remoteRender && !liqglo.useNetRman));
		m_frameScriptJob.cleanupCommands.push_back(cmd);// why cleanupCommand? not command or childJob? Is it a bug?
	}
}
//
void tFrameScriptJobMgr::addHeroPass(
	const MString &ribFileName__t,
	const MString &framePreCommand__, 
	const MString &frameRenderCommand__
)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::addHeroPass("<<ribFileName__t<<","<<framePreCommand__<<","<<frameRenderCommand__<<")");

	std::stringstream ss;
	MString ribFileName__ = ribFileName__t;
	if ( liqglo.m_dirmaps.length() )
	{  
		ribFileName__ = "\\\"%D(" + ribFileName__t + ")\\\"";      
		LIQDEBUGPRINTF( "==> Set DirMaps : %s.\n", liqglo.m_dirmaps.asChar() );
	}
	if( liqglo.useNetRman ) 
	{
#ifdef _WIN32
		ss << framePreCommand__.asChar() << " netrender %H -Progress \"" << ribFileName__.asChar() << "\"";
#else
		ss << framePreCommand__.asChar() << " netrender %H -Progress " << ribFileName__.asChar();
#endif
	} 
	else 
	{
#ifdef _WIN32
		ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " -Progress \"" << ribFileName__.asChar() << "\"";
#else
		ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " -Progress " << ribFileName__.asChar();
#endif
	}
	liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
	if( liqglo.m_alfredExpand ) 
		cmd.alfredExpand = true;

	cmd.alfredServices = liqglo.m_alfredServices.asChar();
	cmd.alfredTags     = liqglo.m_alfredTags.asChar();
	m_frameScriptJob.commands.push_back(cmd);
}
//
void tFrameScriptJobMgr::addShadowPass(
				   const MString &ribFileName__,
				   const MString &framePreCommand__, 
				   const MString &frameRenderCommand__
				   )
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::addShadowPass("<<ribFileName__<<","<<framePreCommand__<<","<<frameRenderCommand__<<")");

	std::stringstream ss;
	if( liqglo.useNetRman ) 
	{
#ifdef _WIN32
		ss << framePreCommand__.asChar() << " netrender %H -Progress \"" << ribFileName__.asChar() << "\"";
#else
		ss << framePreCommand__.asChar() << " netrender %H -Progress " << ribFileName__.asChar();
#endif
	} else {
#ifdef _WIN32
		ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " \"" << ribFileName__.asChar() << "\"";
#else
		ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " " << ribFileName__.asChar();
#endif
	}
	liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
	if( liqglo.m_alfredExpand ) 
		cmd.alfredExpand = true;

	cmd.alfredServices = liqglo.m_alfredServices.asChar();
	cmd.alfredTags     = liqglo.m_alfredTags.asChar();
	m_frameScriptJob.commands.push_back(cmd);
}
//
void tFrameScriptJobMgr::cleanHeroPass(const MString &framePreCommand__,
									   const MString &ribFileName__
									   )
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::cleanHeroPass("<<framePreCommand__<<","<<ribFileName__<<")");

	std::stringstream ss;
#ifdef _WIN32
	ss << framePreCommand__.asChar() << " " << RM_CMD << " \"" << ribFileName__.asChar() << "\"";
#else
	ss << framePreCommand__.asChar() << " " << RM_CMD << " " << ribFileName__.asChar();
#endif
	m_frameScriptJob.cleanupCommands.push_back(liqRenderScript::Cmd(ss.str(), liqglo.remoteRender));

}
//
void tFrameScriptJobMgr::cleanShadowPass(const MString &framePreCommand__,
										 const MString &ribFileName__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::cleanShadowPass("<<framePreCommand__<<","<<ribFileName__<<")");

	std::stringstream ss;
#ifdef _WIN32
	ss << framePreCommand__.asChar() << " " << RM_CMD << " \"" << ribFileName__.asChar() << "\"";
#else
	ss << framePreCommand__.asChar() << " " << RM_CMD << " " << ribFileName__.asChar();
#endif
	m_frameScriptJob.cleanupCommands.push_back(liqRenderScript::Cmd(ss.str(), liqglo.remoteRender));

}
//
void tFrameScriptJobMgr::cleanShadowRibGen(const MString &framePreCommand__,
										   const MString &ribFileName__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::cleanShadowRibGen("<<framePreCommand__<<","<<ribFileName__<<")");

	std::stringstream ss;
#ifdef _WIN32
	ss << framePreCommand__.asChar() << " " << RM_CMD << " \"" << ribFileName__.asChar() << "\"";
#else
	ss << framePreCommand__.asChar() << " " << RM_CMD << " " << ribFileName__.asChar();
#endif
	m_frameScriptJob.cleanupCommands.push_back(liqRenderScript::Cmd(ss.str(), liqglo.remoteRender));

}
//
void tFrameScriptJobMgr::viewHeroPassImage(const MString &imageName__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::viewHeroPassImage("<<imageName__<<")");

	m_frameScriptJob.chaserCommand = (std::string( "sho \"" ) + imageName__.asChar() + "\"" );
}
//
void tFrameScriptJobMgr::viewShadowPassImage(const MString &imageName__)
{
	CM_TRACE_FUNC("tFrameScriptJobMgr::viewShadowPassImage("<<imageName__<<")");

	m_frameScriptJob.chaserCommand = (std::string( "sho \"" ) + imageName__.asChar() + "\"" );
}