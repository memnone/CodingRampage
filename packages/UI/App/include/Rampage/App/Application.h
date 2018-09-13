/** @file Application.h
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
#ifndef _RAMPAGE_APP_APPLICATION_H_
#define _RAMPAGE_APP_APPLICATION_H_

//------------------------------------------------------------------------------

#include <Rampage/Sys/XMLParser.h>
#include <Rampage/Sys/Context.h>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

/** Exceptions */
MESSAGE_DEF(MsgApplication, Message)

//------------------------------------------------------------------------------

/** Application skelton */
class Application {
public:
	/** Constructs Application */
	Application();
	/** Destroys Application */
	virtual ~Application();
	/** Main application method */
	virtual int main(int argc, char *argv[]);

protected:
	/** Abstract run method */
	virtual void run(int argc, char *argv[]) = 0;

	inline XMLParser* xmlparser() {
		return pParser.get();
	}
	inline const XMLParser* xmlparser() const {
		return pParser.get();
	}
	inline XMLContext* xmlcontext() {
		return pXMLContext;
	}
	inline const XMLContext* xmlcontext() const {
		return pXMLContext;
	}
	inline Context* context() {
		return pContext.get();
	}
	inline const Context* context() const {
		return pContext.get();
	}


private:
	XMLParser::Ptr pParser;
	XMLContext* pXMLContext;
	Context::Ptr pContext;
};

//------------------------------------------------------------------------------

};	// namespace

#endif /*_RAMPAGE_APP_APPLICATION_H_*/
