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
#ifndef _RAMPAGE_SYS_DEFS_H_
#define _RAMPAGE_SYS_DEFS_H_

//------------------------------------------------------------------------------

#include <Rampage/Sys/Thread.h>
#include <Rampage/Sys/Message.h>
#include <Rampage/Sys/Parallels.h>
#include <functional>
#include <stdexcept>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

typedef std::function<void()> Function;

//------------------------------------------------------------------------------

/** Assert */
class Assert {
public:
	/** Context */
	class Context {
	public:
		friend class Assert;

		/** Creates linked list of messages */ 
		explicit inline Context(const char* info) : context(nullptr), info(info) {}
		/** Creates linked list of messages */ 
		explicit inline Context(const Context& context, const char* info) : context(&context), info(info) {}

	private:
		const Context *context;
		const char *info;
	};

	/** Throw an exception is expression=false */
	static void valid(bool expression, const char* format, ...);
	/** Throw an exception is expression=false */
	static void valid(bool expression, const Context& context, const char* format, ...);
};

//------------------------------------------------------------------------------

class ScopeGuard {
public:
	typedef rampage::shared_ptr<ScopeGuard> Ptr;
	/** Guard function */
	typedef rampage::Function Function;

	/** Set guard function */
	ScopeGuard(Function function) : function(function) {
	}
	/** Run guard function on object deletion */
	~ScopeGuard() {
		function();
	}
	/** Run guard function on demand */
	void run() {
		function();
	}

private:
	Function function;
};

//------------------------------------------------------------------------------

/** rampage::Thread helper class */
class ThreadTask : protected rampage::Runnable {
public:
	typedef rampage::shared_ptr<ThreadTask> Ptr;
	/** Task function */
	typedef rampage::Function Function;

	/** Task construction */
	ThreadTask(Function function = nullptr, rampage::Thread::Priority priority = rampage::Thread::NORMAL, rampage::MSecTmU32 timeOut = rampage::MSEC_TM_U32_INF) : timeOut(timeOut), function(function), terminating(false) {
		if (!thread.start(this))
			throw rampage::Message(rampage::Message::LEVEL_CRIT, "ThreadTask::ThreadTask(): Unable to start thread");
		(void)thread.setPriority(priority); // ignore retval
	}
	~ThreadTask() {
		terminating = true;
		ev.set(true);
		(void)thread.join(timeOut); // ignore retval
	}
	/** Set new thread task */
	void start(Function function = nullptr) {
		if (function)
			this->function = function; // atomic
		ev.set(true);
	}
	/** Terminate or not */
	void setTerminate(bool terminate = true) {
		terminating = true;
	}
	/** Is terminating? */
	bool isTerminating() const {
		return terminating;
	}

protected:
	/** Thread */
	rampage::Thread thread;
	/** New task */
	rampage::Event ev;
	/** Time to stop */
	rampage::MSecTmU32 timeOut;
	/** Stop condition variable */
	bool terminating;
	/** Task function */
	Function function;

	/** Runnable: thread function */
	virtual void run() {
		for (;;) {
			if (!ev.wait(timeOut))
				continue;
			ev.set(false);
			if (terminating)
				break;
			const Function function = this->function; // atomic
			if (function)
				function();
		}
	}
};

//------------------------------------------------------------------------------

/** rampage::Parallels helper class */
class ParallelsTask : protected rampage::Runnable {
public:
	typedef rampage::shared_ptr<ParallelsTask> Ptr;
	/** Task function */
	typedef std::function<void(ParallelsTask*)> Function;

	/** Task construction */
	ParallelsTask(rampage::Parallels* parallels, Function function, rampage::Thread::Priority priority = rampage::Thread::LOWEST, rampage::MSecTmU32 timeOut = rampage::MSEC_TM_U32_INF) : function(function), stopping(false) {
		// setup Parallels
		if (parallels == nullptr)
			throw rampage::Message(rampage::Message::LEVEL_CRIT, "ParallelsTask::ParallelsTask(): Parallels required");
		// launch Parallels
		for (size_t t = (size_t)parallels->getNumOfThreads(); t > 0; --t) {
			rampage::Job* job = parallels->startJob(this);
			if (!job)
				throw rampage::Message(rampage::Message::LEVEL_CRIT, "ParallelsTask::ParallelsTask(): Unable to start job");
			job->setThreadPriority(priority); // ignore retval
		}
		// wait for completion or stop now
		if (!parallels->joinJobs(timeOut)) {
			stopping = true;
			(void)parallels->joinJobs(rampage::MSEC_TM_U32_INF); // ignore retval
		}
		// check for exceptions
		rampage::CriticalSectionWrapper csw(cs);
		if (!message.empty())
			throw message;
	}
	/** Stop condition */
	bool stop() const {
		return stopping;
	}

protected:
	/** Stop condition variable */
	bool stopping;
	/** Task function */
	Function function;
	/** Task critical section */
	rampage::CriticalSection cs;
	/** Task exception */
	rampage::Message message;

	/** Runnable: parallels thread function */
	virtual void run() {
		try {
			function(this);
		}
		catch (const rampage::Message& msg) {
			rampage::CriticalSectionWrapper csw(cs);
			if (message.empty())
				message = msg;
		}
		catch (const std::exception& ex) {
			rampage::CriticalSectionWrapper csw(cs);
			if (message.empty())
				message = rampage::Message(rampage::Message::LEVEL_CRIT, "ParallelsTask::run(): %s", ex.what());
		}
		catch (...) {
			rampage::CriticalSectionWrapper csw(cs);
			if (message.empty())
				message = rampage::Message(rampage::Message::LEVEL_CRIT, "ParallelsTask::run(): unknown exception");
		}
	}
};

//------------------------------------------------------------------------------

};	// namespace

//------------------------------------------------------------------------------

#endif /*_RAMPAGE_SYS_DEFS_H_*/
