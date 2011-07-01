
#include <liqFrameScriptMgr.h>
#include <liqRenderScript.h>

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
	m_frameScriptJob.title = title;

}
//
void tFrameScriptJobMgr::addInstanceJob(  const bool isInstance,
					const std::string &title
					)
{ 
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