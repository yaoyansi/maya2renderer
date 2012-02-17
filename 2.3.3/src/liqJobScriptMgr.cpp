
#include <liqJobScriptMgr.h>
 
#include <sstream>
#include <liqRenderScript.h>
#include <liqGlobalVariable.h>


tJobScriptMgr::tJobScriptMgr(liqRenderScript& script)
:m_jobScript(script)
{
	
}
//
tJobScriptMgr::~tJobScriptMgr()
{

}
//
void tJobScriptMgr::setCommonParameters(
	const std::string &renderJobName__,
	const bool useNetRman__,
	const liquidlong m_minCPU__,
	const liquidlong m_maxCPU__,
	const MString &m_dirmaps__
	)
{
	m_jobScript.title = renderJobName__;

	if( useNetRman__ ) 
	{
		m_jobScript.minServers = m_minCPU__;
		m_jobScript.maxServers = m_maxCPU__;
	} else {
		m_jobScript.minServers = 1;
		m_jobScript.maxServers = 1;
	}

	if ( m_dirmaps__.length() )
		m_jobScript.dirmaps = m_dirmaps__.asChar();
}
//
void tJobScriptMgr::addJob(
	const std::string &title, 
	const std::string &command, const bool remote
)
{
	liqRenderScript::Job job;
	job.title = title;
	job.commands.push_back( liqRenderScript::Cmd( command, remote ) );
	m_jobScript.addJob( job );
}
//
void tJobScriptMgr::addDefferedJob(const int currentBlock__,
								   const unsigned int frameIndex__,
								   const MString &framePreCommand__,
								   const MString &frameRibgenCommand__)
{
	liqRenderScript::Job deferredJob;
	addDefferedJob(deferredJob, currentBlock__, frameIndex__,
		framePreCommand__, frameRibgenCommand__			
		);
	m_jobScript.addJob(deferredJob);
}
//
void tJobScriptMgr::addDefferedJob(
									  liqRenderScript::Job &deferredJob__,
									  const int currentBlock__,
									  const unsigned int frameIndex__,
									  const MString &framePreCommand__,
									  const MString &frameRibgenCommand__
									  )
{
	std::stringstream ribGenExtras;
	//Note:  -ribName is set to liqglo.liqglo_sceneName originally. 
	//       Because we replace liqglo.liqglo_sceneName with liquidTransGetSceneName(), and delete liqglo.liqglo_sceneName,
	//       we use liqglo.liqglo_ribName to store the ribName which passed by commandline parameter '-ribName'
	//  [2/17/2012 yaoyansi]
	assert(0&&"warrning: ribName is store in liqglo.liqglo_ribName instead of liqglo.liqglo_sceneName.[2/17/2012 yaoyansi]");
	// ribGenExtras << " -progress -noDef -nop -noalfred -projectDir " << liqglo_projectDir.asChar() << " -ribName " << liqglo.liqglo_ribName.asChar() << " -mf " << liqglo.tempDefname.asChar() << " -t ";
	ribGenExtras << " -progress -noDef -projectDir " << liqglo.liqglo_projectDir.asChar() << " -ribName " << liqglo.liqglo_ribName.asChar() << " -fl ";

	unsigned lastGenFrame( ( frameIndex__ + liqglo.m_deferredBlockSize ) < liqglo.frameNumbers.size() ? frameIndex__ + liqglo.m_deferredBlockSize : liqglo.frameNumbers.size() );

	//liquidMessage2(messageInfo, ">>> frameIndex = %d m_deferredBlockSize = %d frameNumbers.size = %d lastGenFrame = %d\n",frameIndex,m_deferredBlockSize,frameNumbers.size(),lastGenFrame );

	for( unsigned outputFrame( frameIndex__ ); outputFrame < lastGenFrame; outputFrame++ )
	{  
		ribGenExtras << liqglo.frameNumbers[ outputFrame ];
		ribGenExtras << (( outputFrame != ( lastGenFrame - 1 ) )? ", " : " ");
		// liquidMessage2(messageInfo, "\t outputFrame = %d\n", outputFrame );
	}
	std::stringstream titleStream;
	titleStream << liquidTransGetSceneName().asChar() << "FrameRIBGEN" << currentBlock__;
	deferredJob__.title = titleStream.str();

	std::stringstream ss;
	ss << framePreCommand__.asChar() << " " << frameRibgenCommand__.asChar() << ribGenExtras.str() << " " <<  liqglo.tempDefname.asChar();
	liqRenderScript::Cmd cmd( ss.str(), liqglo.remoteRender );
	cmd.alfredServices = liqglo.m_defGenService.asChar();
	cmd.alfredTags     = liqglo.m_defGenKey.asChar();
	if( liqglo.m_alfredExpand ) 
		cmd.alfredExpand = true;

	deferredJob__.commands.push_back(cmd);

}
//
void tJobScriptMgr::cleanupDefferedJob()
{
	std::stringstream ss;
	ss << RM_CMD << " " << liqglo.tempDefname.asChar();
	m_jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );

}
void tJobScriptMgr::cleanupRenderScript(const MString &renderScriptName__)
{
	std::stringstream ss;
	ss << RM_CMD << " " << renderScriptName__.asChar();
	m_jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );

}
void tJobScriptMgr::cleanupPostJob(const MString &m_postJobCommand__)
{
	m_jobScript.cleanupCommands.push_back( liqRenderScript::Cmd(m_postJobCommand__.asChar(), (liqglo.remoteRender && !liqglo.useNetRman) ) );

}
//
void tJobScriptMgr::writeRenderScript(const renderScriptFormat format, const MString &renderScriptName__)
{
	if( format == ALFRED ) 
		m_jobScript.writeALF( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName__, liqglo.liqglo_projectDir ).asChar() );
	if( format == XML ) 
		m_jobScript.writeXML( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName__, liqglo.liqglo_projectDir ).asChar() );

}