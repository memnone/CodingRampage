/** @file Data.h
 * 
 * @author	Claudio Zito
 *
 * @copyright  Copyright (C) 2018 CLaudio Zito, University of Birmingham, UK
 *
 * @based on Golem framework developed by Marek Kopicki & Claudio Zito
 *
 * @license  This file copy is licensed to you under the terms described in
 *           the License.txt file included in this distribution.
 *
 */

#pragma once
#ifndef _RAMPAGE_SYS_DATA_H_
#define _RAMPAGE_SYS_DATA_H_

//------------------------------------------------------------------------------

#include <Rampage/Sys/XMLParser.h>
#include <Rampage/Sys/Context.h>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

void XMLData(const std::string &attr, Message::Level& val, XMLContext* context, bool create = false);
void XMLData(const std::string &attr, Thread::Priority& val, XMLContext* context, bool create = false);

//------------------------------------------------------------------------------

/** Message stream setup */
void XMLData(MessageStream::Desc::Ptr& desc, XMLContext* context, bool create = false);

/** Program context setup */
void XMLData(Context::Desc& desc, XMLContext* context, bool create = false);

//------------------------------------------------------------------------------

};	// namespace

#endif /*_RAMPAGE_SYS_DATA_H_*/
