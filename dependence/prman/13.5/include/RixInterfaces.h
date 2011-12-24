/* $Revision: #1 $  (Pixar - RenderMan Division) $Date: 2007/07/06 $ */
/*
** Copyright (c) 2006 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**                      RESTRICTED RIGHTS NOTICE
**       
** Use, duplication, or disclosure by the Government is subject to the
** following restrictions:  For civilian agencies, subparagraphs (a) through
** (d) of the Commercial Computer Software--Restricted Rights clause at
** 52.227-19 of the FAR; and, for units of the Department of Defense, DoD
** Supplement to the FAR, clause 52.227-7013 (c)(1)(ii), Rights in
** Technical Data and Computer Software.
**
** Pixar
** 1200 Park Ave.
** Emeryville, CA  94608
*/

#ifndef RIX_INTERFACE_H
#define RIX_INTERFACE_H

/** 
    \file RixInterfaces.h
    \page index RixInterfaces

    RixInterfaces are RenderMan interface extensions.  An RixInterface
    is simply a C++ class that provides a collection of related methods.
    For example, the RixMessages class provides a standardized way to report
    errors and warnings with optional suppression of duplicate messages.

    An interface is obtained by calling the GetRixInterface method 
    of a context with an identifier from the #RixInterfaceId enum.
    For example, in a shader plugin:
    \code
    RixMessages* msgs = (RixMessages*) rslCtx->GetRixInterface(k_RixMessages);
    msgs->Warning("Are you sure about this?");
    \endcode
    The generic interface that is returned must be cast to the appropriate
    type before use.

    From a procedural plugin, first call 
    <a href="../../users_guide/rxextensions.html#interfaces">
    RxGetRixContext</a> to obtain a context:
    \code
    RixContext* context = RxGetRixContext();
    RixMessages* msgs = (RixMessages*) context->GetRixInterface(k_RixMessages);
    \endcode
    Not all interfaces are available from a given context.  For example, the
    global RixContext does not permit access to per-thread data.

    Interfaces should never be deleted.  Most interfaces are thread safe and
    can be used indefinitely.  For example, rather than fetching the
    RixMessages interface each time a warning is printed, a plugin can store
    the interface in a global variable and reuse it as needed.
    Some interfaces are transient, however: in particular, an RixStorage
    interface for per-thread or local data can be used only in the context
    from which it was obtained.

    For more information, browse the documentation for these classes:
    - RixContext
    - RixInterface, #RixInterfaceId
    - RixStorage
    - RixThreadUtils, RixMutex
    - RixMessages
    - RixStats, RixXmlFile
*/

#include <stddef.h>		// for size_t

//! Identifiers for Rix interfaces.
enum RixInterfaceId {
    k_RixThreadUtils = 0,	///< Id for RixThreadUtils interface.
    k_RixMessages,		///< Id for RixMessages interface.
    k_RixStats,			///< Id for RixStats interface.
    k_RixGlobalData,		///< Id for global RixStorage interface.
    k_RixThreadData,		///< Id for per-thread RixStorage interface.
    k_RixLocalData		///< Id for local RixStorage interface.
};


/// Base class for all Rix interfaces.  
/// Interfaces should never be deleted.  Most interfaces are thread safe
/// and can be used indefinitely, but some interfaces can be used only in
/// the context from which they were obtained.
class RixInterface {
public:
    /// Get the version number of this interface.  Different interfaces
    /// might have different version numbers in a given release.
    virtual int GetVersion() const { return m_version; }

protected:
    /// Version number of this interface.
    int m_version;

    /// Interfaces should not be constructed by users.  
    RixInterface(int version) : m_version(version) { }

    /// Interfaces should not be deleted by users.  
    virtual ~RixInterface() { }
};


/// Rix interfaces are obtained from an RixContext.  Not all interfaces are
/// available from a given RixContext.  For example, a global RixContext does
/// not permit access to per-thread data.
class RixContext {
public:
    /// Get the specified interface from this context.  The generic interface
    /// that is returned must be cast to the appropriate type before use.
    virtual RixInterface* GetRixInterface(RixInterfaceId id) const;

    /// Destructor is for internal use only
    virtual ~RixContext() { }
};


/// A class that encapsulates a mutual exclusion object.
/// This object can be used to lock access to shared data
/// to prevent contention from multiple threads.
///
/// NOTE: This is not a high performance implementation; for
///       best performance one should utilize native platform
///       locks.
class RixMutex {
public:
    /// Virtual destructor
    virtual ~RixMutex() { }

    /// Lock access
    virtual void Lock() = 0;
    
    /// Unlock and allow access 
    virtual void Unlock() = 0;
};


/// This object is used to obtain an RixMutex object
/// that can be used for locking access to shared 
/// global memory
class RixThreadUtils : public RixInterface {
public:
    /// Get a new RixMutex object.  NOTE: It must be deleted.
    virtual RixMutex* NewMutex() const = 0;

protected:
    /// Constructor is for internal use only.
    RixThreadUtils() : RixInterface(1) { }
};


/// An object that can be used to print warnings, errors,
/// or info in a thread safe way from within the renderer
class RixMessages : public RixInterface {
public:
    /**
        Report an error, with printf-style formatting.  For example:
        \code
            ReportError("Plugin failed, status %d", status);
        \endcode
        Duplicate error messages are suppressed.
    */
    virtual void Error(const char* format, ...) = 0;

    /// Report an error, with no suppression of duplicate messages.
    virtual void ErrorAlways(const char* format, ...) = 0;

    /// Report a warning, suppressing duplicate messages.
    virtual void Warning(const char* format, ...) = 0;

    /// Report a warning, with no suppression of duplicate messages.
    virtual void WarningAlways(const char* format, ...) = 0;

    /// Report information, suppressing duplicate messages.
    virtual void Info(const char* format, ...) = 0;

    /// Report information, with no suppression of duplicate messages.
    virtual void InfoAlways(const char* format, ...) = 0;

protected:
    /// Constructor is for internal use only.
    RixMessages() : RixInterface(1) { }
};


/// Interface for including user statistics in XML file.  Thread safe.
///
/// Plugins can report elapsed time and peak memory usage statistics via
/// AddTimerStat and AddMemoryStat.  Other user-defined statistics can be
/// reported via AddReporter.  If statistics are enabled, plugin statistics
/// are reported at the end of each frame, after the built-in statistics are
/// reported.
///
/// Note that shader plugins must take care to ensure thread safety when
/// recording statistics in global variables. Controlling access with a mutex
/// is straightforward. Alternatively, statistics can be recorded in
/// per-thread data and then combined at the end of a frame. See the RSL
/// Plugin application note or the reference documentation for
/// RslContext::SetThreadData for more information.
class RixStats : public RixInterface {
public:
    /// Add a timer statistic, which is simply a pointer to a float into which
    /// the plugin has accumulated timing information (in seconds).  
    /// The name must be a valid XML token; the description may be empty.
    /// A duplicate call with the same name as a previously added statistic is
    /// ignored (a warning is generated if a different pointer is specified).
    /// The name and description are copied.
    virtual void AddTimerStat(float* seconds, const char* name,
			      const char* description) = 0;

    /// Add a memory statistic, which is simply a pointer to a size_t into
    /// which the plugin has accumulated memory usage information (in bytes).
    /// The name must be a valid XML token; the description may be empty.
    /// A duplicate call with the same name as a previously added statistic is
    /// ignored (a warning is generated if a different pointer is specified).
    /// The name and description are copied.
    virtual void AddMemoryStat(size_t* bytes, const char* name, 
			       const char* description) = 0;

    /// A reporting function takes a RixXmlFile and writes to it using
    /// WriteXml and WriteText.  
    typedef void (*Reporter)(class RixXmlFile* file);

    /**
        Register a statistics reporter, which is called at the end of each
        frame after built-in statistics are reported (if statistics are
        enabled).  Duplicate calls with the same reporter are ignored.
        Here is an example of a simple reporting function:
        \code
        void myReporter(RixXmlFile* file)
        {
           file->WriteXml ("<stats name=\"myPlugin\">\n");
           file->WriteXml ("    <int name=\"count\"> %i </int>\n", myCounter);
           file->WriteXml ("    <string name=\"info\">\n");
           file->WriteText("        %s\n", myInfo);
           file->WriteXml ("    </string>\n");
           file->WriteXml ("</stats>\n");
        }
        \endcode
    */
    virtual void AddReporter(Reporter func) = 0;

protected:
    /// Constructor is for internal use only.
    RixStats() : RixInterface(1) { }
};


/// An XML file handle, which is passed to a statistics reporter (see
/// RixStats::AddReporter).
class RixXmlFile {
public:
    /// Write arbitrary XML.  No encoding is performed, so be careful to avoid
    /// the use of special characters (e.g. the less-than symbol).  Users are
    /// encouraged to generate XML that matches the RenderMan statistics XML
    /// schema (e.g. to enable use of the default XML stylesheet).  See
    /// Application Note #43 (Using XML Frame Statistics) for details.
    virtual void WriteXml(const char* format, ...) = 0;

    /// Write arbitrary text to XML file, encoding special characters 
    /// like "&lt".
    virtual void WriteText(const char* format, ...) = 0;

    /// Virtual destructor
    virtual ~RixXmlFile() { }
};


/// A cleanup function can be associated with data in RixStorage.
typedef void (*RixCleanupFunc)(RixContext* context, void* data);


/**
    RixStorage allows plugins to store and share arbitrary data
    by associating it with an arbitrary key.  For example, a shader plugin
    might share per-thread data as follows:
    \code
    RixStorage* storage = (RixStorage*) 
        rslContext->GetRixInterface(k_RixThreadData);
    void* mydata = storage->Get("mydata");
    if (mydata == NULL) {
        mydata = MakeData();
	storage->Set("mydata", mydata, CleanupData);
    }
    \endcode
    This code operates as follows:
    - Get the per-thread data storage interface from the RslContext.
    - Look up the key to see if the data already exists.
    - If not, allocate the data and save it in per-thread storage.
    - The specified cleanup function is called when the thread exits
      (typically at the end of a frame).

    Per-thread storage is thread-safe, but per-frame storage must be locked:
    \code
    RixStorage* storage = (RixStorage*) rslCtx->GetRixInterface(k_RixFrameData);
    storage->Lock();
    void* myglobal = storage->Get("myglobal");
    if (myglobal == NULL) {
        myglobal = MakeData();
	storage->Set("myglobal", myglobal, CleanupData);
    }
    storage->Unlock();
    \endcode

    A cleanup function has a prototype like the following:
    \code
    void myCleanup(RixContext* context, void* data);
    \endcode
    The RixContext argument allows the cleanup function to obtain interfaces
    for reporting errors, etc.  Note that a cleanup fuction for per-thread
    data can access the per-thread RixStorage interface (e.g. for maintaining
    memory usage statistics).  But per-thread storage is not accessible in a
    cleanup function for per-frame data.
*/
class RixStorage : public RixInterface {
public:
    /// Get the data associated with the given key, or NULL if there is none.
    virtual void* Get(const char* key) = 0;

    /// Set the data associated with the given key, along with an optional
    /// cleanup function.  Any previously associated data is discarded
    /// (calling its cleanup function, if any).  The key is copied.
    virtual void Set(const char* key, void* data, 
		     RixCleanupFunc cleanup = NULL) = 0;

    /// Clear any data associated with the given key, calling its cleanup
    /// function (if any).
    virtual void Clear(const char* key) = 0;

    /// Lock this object.  (Unnecessary unless it's used for global storage.)
    virtual void Lock() = 0;

    /// Unlock this object.
    virtual void Unlock() = 0;

protected:
    /// Constructor is for internal use only.
    RixStorage() : RixInterface(1) { }
};


#endif  // RIX_INTERFACE_H
