/** @file Data.cpp
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

#include <Rampage/Sys/Data.h>
#include <Rampage/Sys/XMLData.h>

//------------------------------------------------------------------------------

using namespace rampage;

//------------------------------------------------------------------------------

void rampage::XMLData(const std::string &attr, Message::Level& val, XMLContext* context, bool create) {
	std::string level;
	XMLData(attr, level, context, create);
	transform(level.begin(), level.end(), level.begin(), tolower);
	val =
		level=="verbose"	?	Message::LEVEL_VERBOSE	:
		level=="debug"		?	Message::LEVEL_DEBUG	:
		level=="info"		?	Message::LEVEL_INFO		:
		level=="warning"	?	Message::LEVEL_WARNING	:
		level=="error"		?	Message::LEVEL_ERROR	:
		level=="crit"		?	Message::LEVEL_CRIT		:
								Message::LEVEL_UNDEF;
}

void rampage::XMLData(const std::string &attr, Thread::Priority& val, XMLContext* context, bool create) {
	std::string level;
	XMLData(attr, level, context, create);
	transform(level.begin(), level.end(), level.begin(), tolower);
	val =
		level=="critical"		?	Thread::TIME_CRITICAL	:
		level=="highest"		?	Thread::HIGHEST			:
		level=="above_normal"	?	Thread::ABOVE_NORMAL	:
		level=="normal"			?	Thread::NORMAL			:
		level=="below_normal"	?	Thread::BELOW_NORMAL	:
		level=="lowest"			?	Thread::LOWEST			:
		level=="idle"			?	Thread::IDLE			:
									Thread::ERROR_RETURN;
}

//------------------------------------------------------------------------------

void rampage::XMLData(MessageStream::Desc::Ptr& desc, XMLContext* context, bool create) {
	desc.reset(new BufferedStream::Desc);
	Message::Level level;
	XMLData("level", level, context, create);
	desc->messageFilter.reset(level == Message::LEVEL_UNDEF ? NULL : new LevelMessageFilter(level));
}

void rampage::XMLData(rampage::Context::Desc& desc, XMLContext* context, bool create) {
	ASSERT(context)
	
	try {
		desc.randSeed._U32[0] = 0;
		XMLData("seed", desc.randSeed._U32[0], context->getContextFirst("rand"), create);
	}
	catch (rampage::MsgXMLParser&) {}
	desc.randSeed._U32[1] = 0;
	if (desc.randSeed._U32[0] == 0)
		desc.randSeed.generate();
	
	XMLData(desc.messageStreamDesc, context->getContextFirst("messages"), create);
	try {
		desc.threadParallels = 0;
		XMLData("threads", desc.threadParallels, context->getContextFirst("parallels"), create);
	}
	catch (rampage::MsgXMLParser&) {}
}

//------------------------------------------------------------------------------
