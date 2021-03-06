/** @file Defs.h
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
#ifndef _RAMPAGE_DEFS_DEFS_H_
#define _RAMPAGE_DEFS_DEFS_H_

#include <assert.h>
#include <cstddef>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

#ifndef ASSERT
#ifdef _DEBUG
	#define ASSERT(x) assert(x);
#else
	#define ASSERT(x)
#endif
#endif

//------------------------------------------------------------------------------

/** Safe object delete */
template <typename _Type> void delete_obj(_Type*& ptr) {
	delete ptr; // safe if allocated or NULL
	ptr = NULL;
}

/** Safe array delete */
template <typename _Type> void delete_arr(_Type*& ptr) {
	delete [] ptr; // safe if allocated or NULL
	ptr = NULL;
}

//------------------------------------------------------------------------------

/** Object creating function from the description. */
#define CREATE_FROM_OBJECT_DESC_0(OBJECT, POINTER) virtual POINTER create() const {\
	OBJECT *pObject = new OBJECT();\
	POINTER pointer(pObject);\
	pObject->create(*this);\
	return pointer;\
}

/** Object creating function from the description. */
#define CREATE_FROM_OBJECT_DESC_1(OBJECT, POINTER, PARAMETER) virtual POINTER create(PARAMETER parameter) const {\
	OBJECT *pObject = new OBJECT(parameter);\
	POINTER pointer(pObject);\
	pObject->create(*this);\
	return pointer;\
}

//------------------------------------------------------------------------------

#define PARAMETER_GUARD(OBJECT, TYPE, NAME, OBJECT_REF)\
struct ParameterGuard##NAME {\
	OBJECT& object;\
	TYPE value;\
	ParameterGuard##NAME(OBJECT& object) : object(object) {\
		value = object.get##NAME();\
	}\
	~ParameterGuard##NAME() {\
		object.set##NAME(value);\
	}\
} parameterGuard##NAME(OBJECT_REF)

//------------------------------------------------------------------------------

};	// namespace

#endif /*_RAMPAGE_DEFS_DEFS_H_*/
