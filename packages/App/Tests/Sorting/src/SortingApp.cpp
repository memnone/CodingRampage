/** @file SortingApp.cpp
 * 
 * @author	Claudio Zito
 *
 * @copyright  Copyright (C) 2018 Claudio Zito, University of Birmingham, UK
 *
 * @license  This file copy is licensed to you under the terms described in
 *           the License.txt file included in this distribution.
 *
 */

#include <Rampage/App/Sorting/SortingApp.h>
#include <ctime>

//------------------------------------------------------------------------------

using namespace rampage;

//------------------------------------------------------------------------------

void TestSorting::run(int argc, char *argv[]) {
	const int size = 50;
	
	// FIRST TEST: vector of integers
	std::vector<int> v;
	
	for (auto i = 0; i < size; ++i) {
		v.push_back(std::rand() * 100);
	}

	// print a random generated vector
	writeToConsole<std::vector<int>::iterator>(v.begin(), v.end(), "Random generated vector:");

	// sort the vector with mergesort
	clock_t begin = clock();
	mergesort<std::vector<int>, std::vector<int>::iterator, std::less<int> >(v.begin(), v.end(), std::less<int>());
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	// print the sorted vector and the elapsed time
	writeToConsole<std::vector<int>::iterator>(v.begin(), v.end(), "Sorted vector:");
	context()->write("time=%.9f\n\n", elapsed_secs);

	// SECOND TEST: List od integers 
	std::list<int> l;

	// print a random generated list
	for (auto i = 0; i < size; ++i) {
		l.push_back(std::rand() * 100);
	}
	writeToConsole<std::list<int>::iterator>(l.begin(), l.end(), "Random generated list:");


	// sort the list with mergesort
	begin = clock();
	mergesort<std::list<int>, std::list<int>::iterator, std::less<int> >(l.begin(), l.end(), std::less<int>());
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	// print the sorted list and the elapsed time
	writeToConsole<std::vector<int>::iterator>(v.begin(), v.end(), "Sorted list:");
	context()->write("time=%.9f\n\n", elapsed_secs);
}

int main(int argc, char *argv[]) {
	return TestSorting().main(argc, argv);
}

//------------------------------------------------------------------------------
