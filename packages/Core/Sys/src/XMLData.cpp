/** @file XMLData.cpp
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

#include <Rampage/Sys/XMLData.h>

//------------------------------------------------------------------------------

using namespace rampage;

//------------------------------------------------------------------------------

template <> void rampage::XMLGetValue(std::string &val, const XMLContext* context) {
	ASSERT(context)
	val = context->getValue();
}

template <> void rampage::XMLSetValue(const std::string &val, XMLContext* context) {
	ASSERT(context)
	context->setValue(val);
}

//------------------------------------------------------------------------------

template <> void rampage::XMLGetAttribute(const std::string &attr, std::string &val, const XMLContext* context) {
	ASSERT(context)
	val = context->getAttribute(attr);
}

template <> void rampage::XMLSetAttribute(const std::string &attr, const std::string &val, XMLContext* context) {
	ASSERT(context)
	context->setAttribute(attr, val);
}

//------------------------------------------------------------------------------
