/** @file SortingApp.h
 * 
 * 
 * @author	Claudio Zito
 *
 * @copyright  Copyright (C) 2018 Claudio Zito, University of Birmingham, UK
 *
 * @license  This file copy is licensed to you under the terms described in
 *           the License.txt file included in this distribution.
 *
 */

#pragma once
#ifndef _RAMPAGE_APP_SORTING_H_
#define _RAMPAGE_APP_SORTING_H_

//------------------------------------------------------------------------------

#include <Rampage/App/Application.h>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------
/**
* @brief Test algorithm for the RampageSorting library.
* Testing mergesort and quicksort for std::vector<int> and std::list<int>.
*/
class TestSorting : public Application {
protected:
	/** Prints a container */
	template<typename Itr> void writeToConsole(Itr begin, Itr end, const std::string prefix = "") const {
		context()->write("%s\n[", prefix.c_str());
		for (Itr it = begin; it != end; ++it)
			context()->write("%d ", *it);
		context()->write("]\n");
	}
	/** Runs the application */
	virtual void run(int argc, char *argv[]);
};

int main(int argc, char *argv[]);


//------------------------------------------------------------------------------

};	// namespace

#endif /*_RAMPAGE_APP_SORTING_H_*/
