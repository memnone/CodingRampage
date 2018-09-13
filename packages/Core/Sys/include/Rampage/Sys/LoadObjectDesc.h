/** @file LoadObjectDesc.h
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
#ifndef _RAMPAGE_SYS_LOADOBJECTDESC_H_
#define _RAMPAGE_SYS_LOADOBJECTDESC_H_

//------------------------------------------------------------------------------

#include <Rampage/Sys/Context.h>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

/** Loads driver description - the library function must be implemented in each device library */
typedef void (*LoadObjectDesc)(void* pContext, void *pXMLContext, void* pDesc);

//------------------------------------------------------------------------------

class XMLContext;

/** Library function template */
template <typename _Desc, typename _DescPtr> void loadObjectDesc(Context* context, XMLContext* xmlcontext, _DescPtr* pObjectDesc) {
	using namespace rampage;

	// initialise context in a module
	context->initModule();

	// Create description and load xml configuration
	_Desc* pDesc = new _Desc;
	pObjectDesc->reset(pDesc);
	XMLData(*pDesc, xmlcontext);
}

//------------------------------------------------------------------------------

};	// namespace

//------------------------------------------------------------------------------

#endif /*_RAMPAGE_SYS_LOADOBJECTDESC_H_*/
