
#include <liqRenderScript.h>

#include <cassert>
#include <sstream>
#include <fstream>
#include <boost/bind.hpp>

#include <maya/MString.h>

#include <liquid.h>
#include <liqIOStream.h>


#if defined(_WIN32) /*&& !defined(DEFINED_LIQUIDVERSION)*/
extern const char * LIQUIDVERSION ;
#endif

liqRenderScript::liqRenderScript()
{
	clear();
}
//
int liqRenderScript::addJob(const Job &job, unsigned int parentJobID)
{
	int jobId = popNextJobID();
	assert(jobId > 0);

	if (parentJobID == 0) {
		jobs[jobId] = job;
	} else {
		if (jobs.find(parentJobID) == jobs.end()) {
			throw MString("Error liqRenderScript::addJob() called with non-existant parent job ID");
		}
		jobs[parentJobID].childJobs.push_back(job);
	}

	return jobId;
}
//
void liqRenderScript::clear()
{
	title = "Liquid Job";
	jobs.clear();
	cleanupCommands.clear();
	nextJobID     = 1;
	minServers    = 1;
	maxServers    = 1;
}
//
std::string liqRenderScript::getALF() const
{
	std::stringstream ss;

	ss << "##AlfredToDo 3.0" << std::endl;
	ss << "Job -title {" << title << "(liquid job)}";
	ss << " -comment {#Created By Liquid " << LIQUIDVERSION << "}";
	if ( dirmaps.size() )
		ss << " -dirmaps {" << dirmaps << "}";  
	ss << " -atleast " << minServers << " " << "-atmost " << maxServers;

	if (!jobs.empty()) {
		ss << " -subtasks { ";
		for(std::map<int, Job>::const_iterator job=jobs.begin(); job!=jobs.end(); ++job) {
			ss << std::endl << job->second.getALF(1);    
		}
		ss << std::endl << "}";
	}

	if (!cleanupCommands.empty()) {
		ss << " -cleanup { " << std::endl;
		for(std::vector<Cmd>::const_iterator cmd=cleanupCommands.begin(); cmd!=cleanupCommands.end(); ++cmd) {
			ss << "  " << cmd->getALF() << std::endl;
		}
		ss << "}" << std::endl;
	}

	return ss.str();
}
//
std::string liqRenderScript::getXML() const
{
	std::stringstream ss;

	ss << "<?xml version=\"1.0\"?>" << std::endl;
	ss << "<renderscript>" << std::endl;
	ss << "  <title>" << title << "</title>" << std::endl;
	if ( dirmaps.size() )
		ss << "  <dirmaps>" << dirmaps << " </dirmaps>" << std::endl; 
	ss << "  <minservers>" << minServers << "</minservers>" << std::endl;
	ss << "  <maxservers>" << maxServers << "</maxservers>" << std::endl;

	if (!jobs.empty()) {
		ss << "  <subtasks>" << std::endl;
		for(std::map<int, Job>::const_iterator job=jobs.begin(); job!=jobs.end(); ++job) {
			ss << job->second.getXML(1);    
		}
		ss << "  </subtasks>" << std::endl;
	}

	if (!cleanupCommands.empty()) {
		ss << "  <cleanup>" << std::endl;
		for(std::vector<Cmd>::const_iterator cmd=cleanupCommands.begin(); cmd!=cleanupCommands.end(); ++cmd) {
			ss << "    " << cmd->getXML() << std::endl;
		}
		ss << "  </cleanup>" << std::endl;
	}

	ss << "</renderscript>" << std::endl;

	return ss.str();
}
//
bool liqRenderScript::writeALF(const std::string &filename) const
{
	std::ofstream outFile(filename.c_str());
	if (!outFile) {
		return false;
	}
	outFile << getALF().c_str();
	outFile.close();
	return true;
}
//
bool liqRenderScript::writeXML(const std::string &filename) const
{
	std::ofstream outFile(filename.c_str());
	LIQDEBUGPRINTF( "Writing XML Render Script to: %s!\n", filename.c_str() );	  
	if (!outFile) {
		return false;
	}
	outFile << getXML().c_str();
	outFile.close();
	LIQDEBUGPRINTF( "Finished writing XML Render Script.\n" );
	return true;
} 
//
void liqRenderScript::addLeafDependency(const Job &job)
{
	for(std::map<int, Job>::iterator j=jobs.begin(); j!=jobs.end(); ++j) {
		if ((!j->second.isInstance) && (j->second.title != "liquid pre-job")) {
			j->second.addLeafDependency(job);
		}
	}
}
//
int liqRenderScript::popNextJobID()
{
	return nextJobID++;
}
//-------------------------------------------------------------------
liqRenderScript::Cmd::Cmd()
:command(""), remote(true), alfredExpand(false), alfredTags(""), alfredServices("")
{
}
//
liqRenderScript::Cmd::Cmd(const std::string &c, bool r)
:command(c), remote(r), alfredExpand(false), alfredTags(""), alfredServices("")
{
}
//
liqRenderScript::Cmd::~Cmd()
{
}
//
liqRenderScript::Cmd::Cmd(const liqRenderScript::Cmd& o)
{
	this->command        = o.command;
	this->remote         = o.remote;
	this->alfredExpand   = o.alfredExpand;
	this->alfredTags     = o.alfredTags;
	this->alfredServices = o.alfredServices;
}
//
liqRenderScript::Cmd& liqRenderScript::Cmd::operator=(const liqRenderScript::Cmd& o)
{
	Cmd tmp(o);
	Swap(tmp);
	return *this;
}
//
void liqRenderScript::Cmd::Swap(liqRenderScript::Cmd& o)
{
	using std::swap;

	swap(command,        o.command);
	swap(remote,         o.remote);
	swap(alfredExpand,   o.alfredExpand);
	swap(alfredTags,     o.alfredTags);
	swap(alfredServices, o.alfredServices);
}
//
std::string liqRenderScript::Cmd::getALF() const
{
	std::stringstream ss;

	if (remote) {
		ss << "RemoteCmd";
	} else {
		ss << "Cmd";
	}

	ss << " {" << command << "}";
	if (alfredExpand) {
		ss << " -expand 1";
	}
	if (alfredServices != "") {
		ss << " -service {" + alfredServices + "}";
	}
	if (alfredTags != "") {
		ss << " -tags {" + alfredTags + "}";
	}

	return ss.str();
}
//
std::string liqRenderScript::Cmd::getXML() const
{
	std::stringstream ss;

	ss << "<command remote=\"" << remote << "\"";
	if (alfredServices != "") {
		ss << " alfredservices=\"" << alfredServices << "\"";
	}
	if (alfredTags != "") {
		ss << " alfredtags=\"" << alfredTags << "\"";
	}
	ss << ">" << command << "</command>";

	return ss.str();
}
//------------------------------------------------------------------
liqRenderScript::Job::Job()
: isInstance(false)
{

}
//
liqRenderScript::Job::~Job()
{

}
//
liqRenderScript::Job::Job(const liqRenderScript::Job& o)
{
	this->title           = o.title;
	this->commands        = o.commands;
	this->cleanupCommands = o.cleanupCommands;
	this->chaserCommand   = o.chaserCommand;
	this->childJobs       = o.childJobs;
	this->isInstance      = o.isInstance;
}
//
liqRenderScript::Job& liqRenderScript::Job::operator=(const liqRenderScript::Job& o)
{
	Job tmp(o);
	Swap(tmp);
	return *this;
}
//
void liqRenderScript::Job::Swap(liqRenderScript::Job& o)
{
	using std::swap;

	swap(title, o.title);
	commands.swap(o.commands);
	cleanupCommands.swap(o.cleanupCommands);
	swap(chaserCommand, o.chaserCommand);
	childJobs.swap(o.childJobs);
	swap(isInstance, o.isInstance);
}
//
std::string liqRenderScript::Job::getALF(unsigned int indentLevel) const
{
	std::stringstream ss;

	// setup the correct indentation amount to prepend onto each line
	std::string indent;
	for(unsigned i(0); i<indentLevel; ++i) {
		indent += "  ";
	}

	// if we're an instance task, then the title is the name of the task to instance
	// and nothing more gets done in this job
	if (isInstance) {
		ss << indent << "Instance {" << title << "}";
		return ss.str();
	}

	ss << indent << "Task -title {" << title << "}";

	if (!childJobs.empty()) { 
		ss << " -subtasks {" << std::endl;
		for(std::vector<Job>::const_iterator child=childJobs.begin(); child!=childJobs.end(); ++child) {
			ss << child->getALF(indentLevel+1) << std::endl;
		}
		ss << indent << "}";
	}

	if (!commands.empty()) {
		ss << " -cmds {" << std::endl;
		for(std::vector<Cmd>::const_iterator command=commands.begin(); command!=commands.end(); ++command) {
			ss << indent << "  " << command->getALF() << std::endl;
		}
		ss << indent << "}";
	}

	if (!cleanupCommands.empty()) {
		ss << " -cleanup {" << std::endl;
		for(std::vector<Cmd>::const_iterator cleanup=cleanupCommands.begin(); cleanup!=cleanupCommands.end(); ++cleanup) {
			ss << indent << "  " << cleanup->getALF() << std::endl;
		}
		ss << indent << "}";
	}

	if (chaserCommand != "") {
		ss << " -chaser {" << std::endl;
		ss << indent << "  " << chaserCommand << std::endl;
		ss << indent << "}";
	}

	return ss.str();
}
//
std::string liqRenderScript::Job::getXML(unsigned int indentLevel) const
{
	std::stringstream ss;

	std::string indent;
	for(unsigned i=0; i<indentLevel; ++i) {
		indent += "  ";
	}

	if (isInstance) {
		ss << indent << "<instance>" << title << "</instance>" << std::endl;
		return ss.str();
	}

	ss << indent << "<task>" << std::endl;
	ss << indent << "<title>" << title << "</title>" << std::endl;
	if (!childJobs.empty()) {
		ss << indent << "<subtasks>" << std::endl;
		for(std::vector<Job>::const_iterator child=childJobs.begin(); child!=childJobs.end(); ++child) {
			ss << child->getXML(indentLevel+1);
		}
		ss << indent << "</subtasks>" << std::endl;
	}

	if (!commands.empty()) {
		ss << indent << "<commands>" << std::endl;
		for(std::vector<Cmd>::const_iterator command=commands.begin(); command!=commands.end(); ++command) {
			ss << indent << "  " << command->getXML() << std::endl;
		}
		ss << indent << "</commands>" << std::endl;
	}

	if (!cleanupCommands.empty()) {
		ss << indent << "<cleanup>" << std::endl;
		for(std::vector<Cmd>::const_iterator cleanup=cleanupCommands.begin(); cleanup!=cleanupCommands.end(); ++cleanup) {
			ss << indent << "  " << cleanup->getXML() << std::endl;
		}
		ss << indent << "</cleanup>" << std::endl;
	}       

	if (chaserCommand != "") {
		ss << indent << "<chaser>" << chaserCommand << "</chaser>" << std::endl;
	}     

	ss << indent << "</task>" << std::endl;

	return ss.str();
}
//
void liqRenderScript::Job::addLeafDependency(const liqRenderScript::Job &job)
{
	bool hasChildren = false;
	for(std::vector<Job>::iterator child=childJobs.begin(); child!=childJobs.end(); ++child) {
		if (!child->isInstance) {
			hasChildren = true;
			child->addLeafDependency(job);
		}
	}

	if (!hasChildren) {
		childJobs.push_back(job);
	}
}
//
//
void liqRenderScript::swap(liqRenderScript::Cmd &l, liqRenderScript::Cmd &r)
{
	l.Swap(r);
}
void liqRenderScript::swap(liqRenderScript::Job &l, liqRenderScript::Job &r)
{
	l.Swap(r);
}
//
std::ostream& liqRenderScript::Cmd::Print(std::ostream& o) const
{
	//o<<"liqRenderScript::Cmd-------------"<<endl;
	o<<" cmd={"<<command<<","<<remote<<","<<alfredExpand<<","<<alfredTags<<","<<alfredServices<<"}"<<endl;

	return o;
}
//
std::ostream& operator<<(std::ostream& o, const liqRenderScript::Cmd& cmd)
{
	return cmd.Print(o);
}
//
std::ostream& liqRenderScript::Job::Print(std::ostream& o) const
{
	//o<<"liqRenderScript::Cmd-------------"<<endl;
	o<<" job={"<<title<<","<<chaserCommand<<","<<isInstance<<","<<endl;
	for_each(commands.begin(),        commands.end(),        boost::bind(&liqRenderScript::Cmd::Print, _1, boost::ref(o)));
	for_each(cleanupCommands.begin(), cleanupCommands.end(), boost::bind(&liqRenderScript::Cmd::Print, _1, boost::ref(o)));
	for_each(childJobs.begin(),       childJobs.end(),       boost::bind(&liqRenderScript::Job::Print, _1, boost::ref(o)));
	o<<"}"<<endl;

	return o;
}
//
std::ostream& operator<<(std::ostream& o, const liqRenderScript::Job& job)
{
	return job.Print(o);
}