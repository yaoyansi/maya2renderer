/* $Revision: #1 $  (Pixar - RenderMan Division)	$Date: 2007/07/06 $ */
/*
** Copyright (c) 2006 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**			RESTRICTED RIGHTS NOTICE
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

#ifndef RSLPLUGIN_H
#define RSLPLUGIN_H

// Use of typedefs like RtColor is recommended for new grid-based shadeops.
// For backwards compatibility, they are not automatically included for older
// pointwise shadeops.
#include "ri.h"
#include "RixInterfaces.h"	// RslContext inherits from RixContext

/// Plugin API version number.
#define RSL_PLUGIN_VERSION 3

/** 
    \file RslPlugin.h
    \page index RSL Plugin API Reference

    The RslPlugin API consists of the following classes:
    - RslContext
    - RslArg
    - RslIter
    - RslArrayIter
    
    Here is a typical RSL plugin function, which computes "a = b + c"
    for floating-point values.
    \code
    RSLEXPORT int
    add(RslContext* rslContext, int argc, const RslArg** argv) {
	RslFloatIter a(argv[0]);
	RslFloatIter b(argv[1]);
	RslFloatIter c(argv[2]);

	int n = argv[0]->NumValues();
	for (int i = 0; i < n; ++i) {
	    *a = *b + *c;
	    ++a; ++b; ++c;	// Note: pre-incr is faster than post-incr.
	}
        return 0;
    }
    \endcode
    An iterator is conceptually a pointer that can be dereferenced to access a
    single value and incremented to reach the next value.  Grid data might be
    sparse, however; the increment operator knows how to skip to the next
    active point efficiently.

    An iterator can be used without regard to whether the argument data is
    uniform or varying: incrementing an iterator for a uniform argument has no
    effect.  The number of iterations is typically determined by the number of
    values in the result argument (argv[0]->NumValues()), which might be one
    if all the arguments are uniform.  Plugin functions that return values via
    output arguments must take the detail of all the arguments into account,
    however:
    \code
        int n = RslArg::NumValues(argc, argv);
    \endcode
 
    An alternative interface is available for RSL plugin functions that requires
    access to all the grid data (e.g. for block copies that might include
    data for inactive points).	Here is an example:
    \code
     RslArg* A = argv[0];
     RslArg* B = argv[1];
     RslArg* C = argv[2];
     float *aData, *bData, *cData;
     int aStride, bStride, cStride;
     A->GetData(&aData, &aStride);
     B->GetData(&bData, &bStride);
     C->GetData(&cData, &cStride);

     unsigned int numPoints;
     const RslRunFlag* runFlags = rslContext->GetRunFlags(&numPoints);
 
     for(int i = 0; i < numPoints; ++i) {
	 if (runFlags[i])
	     *aData = *bData + *cData;
	 aData += aStride;
	 bData += bStride;
	 cData += cStride;
     }
    \endcode
    This implementation is far less efficient when grids are sparse.

*/

/// Most shadeops should use iterators to access data, but those that
/// don't use runflags to determine which grid points are active.
typedef unsigned int RslRunFlag;

/// Iterators use an accelaration structure involving small increments.
typedef unsigned int RslIncrType;

/// An RSL plugin function takes a context, number of arguments, and an array
/// of arguments.  A non-zero return value indicates an error.
typedef int (*RslEntryFunc)(class RslContext* ctx,
			    int argc, const class RslArg** argv);

/**
   RslContext contains the grid data required to execute a shadeop.
*/
class RslContext : public RixContext {
public:
    /// Virtual destructor
    virtual ~RslContext() {}

    /// Returns an array of runflags. A value of 1 indicates the grid point
    /// is active, a value of 0 means the grid point is not active.
    virtual const RslRunFlag* GetRunFlags(unsigned int* length) const = 0;

    /// Shader plugins have access to RixInterfaces that provide various kinds
    /// of storage management (per-frame, per-thread, and per-grid),
    /// statistics reporting, error messages, etc.
    virtual RixInterface* GetRixInterface(RixInterfaceId id) const = 0;

    /**
       Get thread-safe global variable storage, which is used as follows:
       \code
       RixStorage* storage = rslContext->GetGlobalStorage();
       storage->Lock();
       void* myglobal = storage->Get("myglobal");
       if (myglobal == NULL) {
           myglobal = MakeData();
	   storage->Set("myglobal", myglobal, CleanupData);
       }
       storage->Unlock();
       \endcode
       This code operates as follows:
       - Get the globals from the RslContext.
       - Lock the globals for thread safety.
       - Look up the key to see if the data already exists.
       - If not, allocate the data and store it in the globals.
         (The optional cleanup function is called at end of frame.)
       - Unlock the globals.
    */
    RixStorage* GetGlobalStorage() const
    {
	return (RixStorage*) GetRixInterface(k_RixGlobalData);
    }

    /**
       Get per-thread storage, which is used as follows:
       \code
       RixStorage* storage = rslContext->GetThreadStorage();
       void* mydata = storage->Get("mydata");
       if (mydata == NULL) {
           mydata = MakeData();
	   storage->Set("mydata", mydata, CleanupData);
       }
       \endcode
       This code operates as follows:
       - Get the per-thread storage from the RslContext.
       - Look up the key to see if the data already exists.
       - If not, allocate the data and store it in the globals.
         (The optional cleanup function is called at end of frame.)
    */       
    RixStorage* GetThreadStorage() const
    {
	return (RixStorage*) GetRixInterface(k_RixThreadData);
    }

    /**
       Get local data storage, which is cleared when the current
       shader set finishes running on the current set of points.
    */
    RixStorage* GetLocalStorage() const
    {
	return (RixStorage*) GetRixInterface(k_RixLocalData);
    }

    /// Set per-thread user data and optional cleanup function.
    /// The cleanup function is called on the user data when the thread
    /// is terminated.  For greater flexibility, use GetThreadStorage.
    void SetThreadData(void* data, RixCleanupFunc cleanup = 0L)
    {
	RixStorage* storage = (RixStorage*) GetRixInterface(k_RixThreadData);
	storage->Set(GetPluginName(), data, cleanup);
    }

    /// Get per-thread user data.
    void* GetThreadData() const
    {
	RixStorage* storage = (RixStorage*) GetRixInterface(k_RixThreadData);
	return storage->Get(GetPluginName());
    }

    /// Set local user data and optional cleanup function.
    /// The cleanup function is called on the user data when the current
    /// shader set finishes running on the current set of points.
    /// For greater flexibility, use GetLocalStorage.
    void SetLocalData(void* data, RixCleanupFunc cleanup = 0L)
    {
	RixStorage* storage = (RixStorage*) GetRixInterface(k_RixLocalData);
	storage->Set(GetPluginName(), data, cleanup);
    }

    /// Get local user data.
    void* GetLocalData() const
    {
	RixStorage* storage = (RixStorage*) GetRixInterface(k_RixLocalData);
	return storage->Get(GetPluginName());
    }

    /// Get the name of this plugin.
    virtual const char* GetPluginName() const = 0;

private:
    // Need to call private methods from iterator constructors.
    template<typename T> friend class RslIter;
    template<typename T> friend class RslArrayIter;

    // Get acceleration info for an iterator with "packed" user data.
    virtual RslIncrType* getIncrList(unsigned int stride) const = 0;
};

/// Plugin function argument (API version 2).  For internal use only.
/// User code should always use the most recent version, RslArg.
class RslArg_v2 {
public:
    /// Virtual destructor
    virtual ~RslArg_v2() {};

    /// Returns true if this argument is a float.  
    virtual bool IsFloat() const = 0;

    /// Returns true if this argument is a point.  
    virtual bool IsPoint() const = 0;

    /// Returns true if this argument is a vector.  
    virtual bool IsVector() const = 0;

    /// Returns true if this argument is a color.  
    virtual bool IsColor() const = 0;

    /// Returns true if this argument is a string.  
    virtual bool IsString() const = 0;

    /// Returns true if this argument is a matrix.  
    virtual bool IsMatrix() const = 0;

    /// Returns true if this argument is an array.  
    virtual bool IsArray() const = 0;

    /// Returns true if this argument is varying
    virtual bool IsVarying() const = 0;

    /// Get the length of an array argument.  The result is undefined
    /// if this argument is not an array (call IsArray first).
    virtual int GetArrayLength() const = 0;

    /// Get the number of values for this argument.  Returns 1 if the
    /// argument is uniform.  Otherwise it returns the number of points
    /// in the context.
    virtual unsigned int NumValues() const = 0;

    /// Get the maximum number of values for the given arguments.
    /// This method should be used to determine the number of iterations
    /// when a plugin function returns values via output arguments.
    static unsigned int NumValues(int argc, const class RslArg** argv);

    /// Get the raw data pointer for this argument from the given context,
    /// along with the stride, which specifies how much to increment the
    /// pointer on each iteration.  (The stride is zero if the argument is
    /// uniform.)  Use with caution!  Do not read or modify values for
    /// inactive points.  Use RslContext::GetRunflags to determine which
    /// points are active.
    virtual void GetData(float** data, int* stride) const = 0;

private:
    // Need to call private methods from iterator constructors.
    template<typename T> friend class RslIter;
    template<typename T> friend class RslArrayIter;

    // Returns (in result parameters) the data pointer and increment list.
    virtual void getInfo(float** data, RslIncrType** incrList,
		 bool* isVarying) const = 0;

    // Returns (in result parameters) the data pointer, increment list, and
    // array length.
    virtual void getArrayInfo(float** data,
		      RslIncrType** incrList, int* arrayLength,
		      bool* isVarying) const = 0;
};


/// An array of RslArg pointers is passed to the RSL plugin function.  
/// The result parameter is always the first argument.
class RslArg : public RslArg_v2
{
public:
    /// Returns true if this argument is a normal.  
    virtual bool IsNormal() const = 0;

    /// Returns true if this argument is writeable.  This is useful in 
    /// varargs plugin functions to verify that output arguments are valid.
    /// An argument is writeable if it's a local variable, a shader output
    /// parameter, or a global variable (e.g. P, N).
    virtual bool IsWriteable() const = 0;

    /// Virtual destructor
    virtual ~RslArg() {};
};


// Implementation of RslArg_v2::NumValues must follow definition of RslArg.
inline unsigned int 
RslArg_v2::NumValues(int argc, const RslArg** argv) 
{
    int m = 1;
    for (int i = 0; i < argc; ++i) {
	int n = argv[i]->NumValues();
	if (n > m)
	    m = n;
    }
    return m;
}


/**
    An iterator is used to access grid data.  Incrementing an iterator skips
    over inactive grid points.  An iterator is constructed from an RslArg
    and used as follows:
    \code
    RslFloatIter a(argv[0]);
    RslFloatIter b(argv[1]);
    RslFloatIter c(argv[2]);

    int n = argv[0]->NumValues();
    for (int i = 0; i < n; ++i) {
	*a = *b + *c;
	++a; ++b; ++c;
    }
    \endcode
*/
template<typename T>
class RslIter {
public:
    /// Construct an iterator from an argument.
    RslIter(const RslArg* arg)
    {
	arg->getInfo(&m_data, &m_incrList, &m_isVarying);
    }

    /// Construct a uniform iterator for user-provided data.
    /// This is useful for optional arguments with default values.
    RslIter(const T* data, const RslContext* ctx) :
	m_data((float*) data),
	m_incrList(ctx->getIncrList(0)),
	m_isVarying(false)
    {
    }

    /// Dereference this iterator, yielding a non-const reference.  This
    /// method is automatically selected when a dereferenced iterator is
    /// the target of an assignment, such as "*a = 0".
    T& operator*() { return *((T*) m_data); }

    /// Get a const reference to the data pointed to by this iterator.
    /// This method is automatically selected by the compiler when
    /// appropriate.
    const T& operator*() const { return *((T*) m_data); }

    /// Increment this iterator to point to the data for the next active
    /// point.	An internal acceleration structure makes this a
    /// constant-time operation.
    RslIter<T>& operator++() 
    {
	m_data += *m_incrList;
	++m_incrList;
	return *this;
    };

    /// Post-increment this iterator.  Returns a copy of the iterator
    /// prior to incrementing, so it's not terribly efficient.	The dummy
    /// integer argument is the standard C++ way of distinguishing between
    /// pre- and post-increment operators.
    RslIter<T> operator++(int) 
    {
	RslIter<T> temp = *this;		// Copy before increment.
	++*this;			// Increment.
	return temp;			// Return old value.
    };

    /// Returns true if the iterator is varying.  Note that uniform iterators
    /// need not be incremented (although it does no harm).
    bool IsVarying() const { return m_isVarying; }

private:
    // Current data pointer.
    float* m_data;

    // Current increment list, which gives fast access to next active point.
    RslIncrType* m_incrList;

    // True if the iterator is varying.
    bool m_isVarying;
};
    

/// Increment operator for matrices must scale the increment.
template<>
inline RslIter<RtMatrix>&
RslIter<RtMatrix>::operator++() 
{
    m_data += *m_incrList * 16;
    ++m_incrList;
    return *this;
};


/**
   An iterator for array arguments.

   ... example here ...
*/
template<typename T>
class RslArrayIter {
public:
    /// Construct an array iterator from an argument.
    RslArrayIter(const RslArg* arg)
    {
	arg->getArrayInfo(&m_data, &m_incrList, &m_length, &m_isVarying);
    }

    /// Construct a uniform array iterator for user-provided data.
    /// This is useful for optional arguments with default values.
    RslArrayIter(const T* data, int length, const RslContext* ctx) :
	m_data((float*) data),
	m_incrList(ctx->getIncrList(0)),
	m_length(length),
	m_isVarying(false)
    {
    }

    /// Dereference this iterator, yielding a pointer to the start
    /// of the array.
    T* operator*() { return (T*) m_data; }

    /// The array index operator can be used to access individual
    /// array members.
    T&  operator[](int x) { return ((T*)m_data)[x]; }

    /// Increment this iterator to point to the array for the next active
    /// point.	An internal acceleration structure makes this a
    /// constant-time operation.
    RslArrayIter<T>& operator++() 
    {
	m_data += *m_incrList * m_length;
	++m_incrList;
	return *this;
    };

    /// Post-increment this iterator.  Returns a copy of the iterator
    /// prior to incrementing, so it's not terribly efficient.	The dummy
    /// integer argument is the standard C++ way of distinguishing between
    /// pre- and post-increment operators.
    RslArrayIter<T> operator++(int) 
    {
	RslArrayIter<T> temp = *this;	// Copy before increment.
	++*this;			// Increment.
	return temp;			// Return old value.
    };
	
    /// Returns true if the iterator is varying.  Note that uniform iterators
    /// need not be incremented (although it does no harm).
    bool IsVarying() const { return m_isVarying; }

    /// Returns the array length.
    int GetLength() const { return m_length; }
	
private:
    // Current data pointer.
    float* m_data;

    // Current increment list, which gives fast access to next active point.
    RslIncrType* m_incrList;

    // Array length.
    int m_length;

    // True if the iterator is varying.
    bool m_isVarying;
};


typedef RslIter<RtFloat>	RslFloatIter;	     ///< Float iterator
typedef RslIter<RtString>	RslStringIter;	     ///< String iterator
typedef RslIter<RtColor>	RslColorIter;	     ///< Color iterator
typedef RslIter<RtVector>	RslVectorIter;	     ///< Vector iterator
typedef RslIter<RtNormal>	RslNormalIter;	     ///< Normal iterator
typedef RslIter<RtPoint>	RslPointIter;	     ///< Point iterator
typedef RslIter<RtMatrix>	RslMatrixIter;	     ///< Matrix iterator

typedef RslArrayIter<RtFloat>	RslFloatArrayIter;   ///< Float array iterator
typedef RslArrayIter<RtString>	RslStringArrayIter;  ///< String array iterator
typedef RslArrayIter<RtColor>	RslColorArrayIter;   ///< Color array iterator
typedef RslArrayIter<RtVector>	RslVectorArrayIter;  ///< Vector array iterator
typedef RslArrayIter<RtNormal>	RslNormalArrayIter;  ///< Normal array iterator
typedef RslArrayIter<RtPoint>	RslPointArrayIter;    ///< Point array iterator
typedef RslArrayIter<RtMatrix>	RslMatrixArrayIter;   ///< Matrix array iterator
    

/// A per-frame init/cleanup function takes an RixContext, which allows it to
/// obtain interfaces for reporting errors, accessing global RixStorage, etc.
typedef void (*RslVoidFunc)(RixContext* context);

/**
    Each plugin must define an RSL function table, which requires two steps.
    First, a array of RslFunction structs is defined:
    \code
        static RslFunction myfunctions[] = {
            { "float sqr(float)", sqr_f, NULL, NULL },
            { "color sqr(color)", sqr_c, NULL, NULL },
            { "point mynoise(point)", mynoise, noiseinit, noisedelete },
            NULL
        };
    \endcode

    Each RslFunction specifies the prototype(s) of a shadeop, along a pointer
    to its entry function.  Overloaded shadeops have multiple entries with
    different prototypes (which might share the same entry point since colors,
    points, and vectors have the same representation).  The last entry of the
    array should be NULL.

    Each RslFunction can also have an optional associated init and cleanup
    function. The init function is called once per frame in a thread safe way
    for EACH function it is associated with. Likewise each cleanup function is
    called once at the end of frame for EACH associated function. The cleanup 
    function will ONLY be called for a function with an associated init function.
   
    Next, the RslFunctionTable is constructed.  It must be called
    "RslPublicFunctions" and it should be exported.  In addition to
    specifying the array of entry functions, an optional initialization
    and cleanup function may be provided.
    \code
        RSLEXPORT RslFunctionTable RslPublicFunctions(myfunctions, myinit, mycleanup);
    \endcode
    The initialization function is executed the first time any function in the
    pluginis called in a given frame, and the cleanup function is called at
    the end of the frame.

    Note that the plugin table must be declared with RSLEXPORT under Windows.
    This declaration has no effect on other platforms, so it's a good idea to
    always include it for portability.
*/
struct RslFunction {
    /// RSL function prototype.
    const char *m_prototype;

    /// Pointer to entry function.
    RslEntryFunc m_entry;

    /// Per-frame initialization function (possibly NULL).
    RslVoidFunc m_initFunc;

    /// Per-frame cleanup function (possibly NULL).
    RslVoidFunc m_cleanupFunc;
};

/// Each plugin should define an RslFunctionTable called "RslPublicFunctions".  
/// \see RslFunction
struct RslFunctionTable {
    /// The function table.
    const RslFunction* m_functions;

    /// Plugin API version number (for internal use only).
    const char m_version;

    /// Per-frame initialization function (possibly NULL).
    RslVoidFunc m_initFunc;

    /// Per-frame cleanup function (possibly NULL).
    RslVoidFunc m_cleanupFunc;

    /// Constructor
    RslFunctionTable(const RslFunction* functions,
		     RslVoidFunc init = NULL, RslVoidFunc cleanup = NULL) :
	m_functions(functions),
	m_version(RSL_PLUGIN_VERSION),
	m_initFunc(init),
	m_cleanupFunc(cleanup)
    {
    }
};

/**
    Under Windows, the plugin table must be declared with RSLEXPORT.  For
    example:
    \code
       RSLEXPORT RslFunction RslPublicFunctions = ...
    \endcode
    This declaration has no effect on other platforms, so it's a good idea to
    always include it for portability.
*/
#ifdef _MSC_VER
#define RSLEXPORT __declspec(dllexport)
#else
#define RSLEXPORT
#endif

#endif /* defined RSLPLUGIN_H */
