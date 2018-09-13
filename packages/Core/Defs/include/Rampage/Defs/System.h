/** @file System.h
 * 
 * Operating system specific headers for Windows, Linux/Cygwin, Apple.
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
#ifndef _RAMPAGE_DEFS_SYSTEM_H_
#define _RAMPAGE_DEFS_SYSTEM_H_

//------------------------------------------------------------------------------

#if !defined(WIN32) && !defined(LINUX) && !defined(__APPLE__)
#error unknown platform
#endif

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0500
#endif
	#define NOMINMAX

#include <windows.h>

#else
#if !defined(UNIX)
#define UNIX
#endif

#endif

//------------------------------------------------------------------------------

#endif /*_RAMPAGE_DEFS_SYSTEM_H_*/
