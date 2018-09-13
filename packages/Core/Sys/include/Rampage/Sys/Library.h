/** @file Library.h
 * 
 * Library tools.
 * 
 * @author	Claudio Zito
 *
 * @copyright  Copyright (C) 2018 Claudio Zito, University of Birmingham, UK
 *
 * @based on Golem framework developed by Marek Kopicki & Claudio Zito
 *
 * @license  This file copy is licensed to you under the terms described in
 *           the License.txt file included in this distribution.
 *
 */

#pragma once
#ifndef _RAMPAGE_SYS_LIBRARY_H_
#define _RAMPAGE_SYS_LIBRARY_H_

//------------------------------------------------------------------------------

#include <Rampage/Defs/Pointers.h>
#include <Rampage/Defs/System.h>
#include <Rampage/Sys/Message.h>
#include <string>
#include <map>
#include <list>

//------------------------------------------------------------------------------

#undef RAMPAGE_LIBRARY_DECLDIR
#define RAMPAGE_LIBRARY_DECLDIR

#ifdef RAMPAGE_LIBRARY_DECLDIR_EXPORT // export DLL
#undef RAMPAGE_LIBRARY_DECLDIR
#define RAMPAGE_LIBRARY_DECLDIR __declspec(dllexport)
#endif

#ifdef RAMPAGE_LIBRARY_DECLDIR_IMPORT // import DLL
#undef RAMPAGE_LIBRARY_DECLDIR
#define RAMPAGE_LIBRARY_DECLDIR __declspec(dllimport)
#endif

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

/** Exceptions */
MESSAGE_DEF(MsgHandle, Message)
MESSAGE_DEF(MsgHandleOpen, MsgHandle)
MESSAGE_DEF(MsgHandleFunc, MsgHandle)

//------------------------------------------------------------------------------

/** Library */
class Handle {
public:
#ifdef WIN32
	typedef HINSTANCE HANDLE; // Windows
	typedef FARPROC FUNCTION; // Windows
#else	// WIN32
	typedef void* HANDLE;
	typedef void* FUNCTION;
#endif	// WIN32
	/** Map */
	typedef std::map<std::string, Handle> Map;
	/** List */
	typedef std::list<Map::iterator> List;

	/** Open library */
	Handle(const std::string& path);
	/** Library path */
	std::string getPath() const;
	/** Library directory */
	std::string getDir() const;
	/** Library name */
	const std::string& getName() const;
	/** Handle */
	HANDLE getHandle() const;
	/** Function */
	FUNCTION getFunction(const char* name);

private:
	/** Description relese */
	static void release(HANDLE* pHandle);
	friend class reference_cnt<HANDLE, Handle>;

	/** Library name */
	std::string name;
	/** Library address */
	shared_ptr<HANDLE, reference_cnt<HANDLE, Handle> > handle;
};

//------------------------------------------------------------------------------

};	// namespace

//------------------------------------------------------------------------------

#endif /*_RAMPAGE_SYS_LIBRARY_H_*/
