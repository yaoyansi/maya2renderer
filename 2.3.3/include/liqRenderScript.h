/*
**
** The contents of this file are subject to the Mozilla Public License Version
** 1.1 (the "License"); you may not use this file except in compliance with
** the License. You may obtain a copy of the License at
** http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis,
** WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
** for the specific language governing rights and limitations under the
** License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions
** created by Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
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

#ifndef liqRenderScript_H
#define liqRenderScript_H


#include <string>
#include <map>
#include <vector>
#include<iosfwd>



/* ______________________________________________________________________
**
** Liquid Job Script Header File
** ______________________________________________________________________
*/


// Class to encapsulate the processes to run after liquid has completed
// generating RIB files
// 
// Initially this supports Pixar's Alfred and a basic XML format. Other formats
// can be added onto this class, or it can be extracted into a class hierarchy
// where new output formats can be added on through subclasses and an API mechanism


class liqRenderScript
{
public:
  // a Cmd object represents a single command line to be run as part of a job
  // needs to be a class rather than just a string, to carry along extra info about running the
  // command to be run (e.g. local or remote, alfred tags, etc)
  class Cmd
  {
  public:
    Cmd();
	explicit Cmd(const std::string &c, bool r);
	virtual ~Cmd();

	Cmd(const Cmd& o);
	Cmd& operator=(const Cmd& o);
	void Swap(Cmd& o);

  public:
    std::string command;
    bool remote;
    bool alfredExpand;
    std::string alfredTags;
    std::string alfredServices;

    std::string getALF() const;
    std::string getXML() const;
  
	std::ostream& Print(std::ostream& o) const;

  private:

  };
  static void swap(Cmd &l, Cmd &r);

  // a Job object encapsulates a single logical task to be run, with additional
  // cleanup and 'chaser' commands (optional GUI driven tasks, e.g. display an image)
  // jobs can be nested to form hierarchical dependencies
  class Job
  {
  public:
    Job();
	virtual ~Job();

	Job(const Job& o);
	Job& operator=(const Job& o);
	void Swap(Job& o);

    std::string getALF(unsigned int indentLevel=0) const;
    std::string getXML(unsigned int indentLevel=0) const;
    
    // adds a job as a dependency of any 'leaf' jobs anywhere under the hierarchy
    // of this job. i.e. any job with no children will get this as a child
    // good for tacking instances onto the end of job trees
    void addLeafDependency(const Job &job);

  public:
    std::string title;
    std::vector<Cmd> commands;
    std::vector<Cmd> cleanupCommands;
    std::string chaserCommand;
    std::vector<Job> childJobs;
    bool isInstance;

	std::ostream& Print(std::ostream& o) const;
  private:

  };
  static void swap(Job &l, Job &r);

public:
  liqRenderScript();
  virtual ~liqRenderScript(){}

  // add a job to the list
  // if a job is a child you need to specify the job ID of the parent
  // the first (main) job will always have an ID of '1'
  // for the main job, or any other job not dependent on anything else
  // you should specify a parent ID of '0' (no parent)
  int addJob(const Job &job, unsigned int parentJobID=0);

  void clear();
  
  std::string getALF() const;
  
  std::string getXML() const;
  
  bool writeALF(const std::string &filename) const;
  
  bool writeXML(const std::string &filename) const;
  
  void addLeafDependency(const Job &job);

public:
  std::string title;
  std::vector<Cmd> cleanupCommands;
  
  unsigned int minServers;
  unsigned int maxServers;
  std::string dirmaps;
  
private:
  int popNextJobID();
    
private:
  std::map<const int, Job> jobs;
  
  int nextJobID;

private:
	liqRenderScript(const liqRenderScript&);
	liqRenderScript& operator=(const liqRenderScript&);
};

std::ostream& operator<<(std::ostream& o, const liqRenderScript::Cmd& renderer);
std::ostream& operator<<(std::ostream& o, const liqRenderScript::Job& renderer);


#endif // liqRenderScript_H
