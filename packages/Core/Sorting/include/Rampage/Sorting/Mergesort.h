/** @file Mergesort.h
 * 
 * Mergesort O(NlogN)
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
#ifndef _RAMPAGE_SORTING_MERGESORT_H_
#define _RAMPAGE_SORTING_MERGESORT_H_

#include <Rampage/Defs/Types.h>
#include <iterator>

//------------------------------------------------------------------------------

namespace rampage {

//------------------------------------------------------------------------------

template<typename Container, typename Itr, typename Cmp> Container merge(Itr begin, Itr mid, Itr end, Cmp less) {
	// Merged and sorted data will be contained here
	Container buffer;

	// Pointers for merging
	Itr left(begin);
	Itr right(mid);
	Itr& leftEnd = mid; // ref, no copy
	Itr& rightEnd = end; // ref, no copy

	while (left != leftEnd && right != rightEnd) 
		buffer.push_back((*left <= *right) ? *left++ : *right++);
	
	// only one of the two next istructions will be actually executed
	buffer.insert(buffer.end(), left, leftEnd);
	buffer.insert(buffer.end(), right, rightEnd);
	return buffer;
}

template<typename Container, typename Itr, typename Cmp> void mergesort(Itr begin, Itr end, Cmp less) {
	const std::iterator_traits<Itr>::difference_type size = std::distance(begin, end);
	if (size < 2)
		return;

	// partition the container into two halves
	Itr middle(begin);
	std::advance(middle, size / 2);

	mergesort<Container, Itr, Cmp>(begin, middle, less);
	mergesort<Container, Itr, Cmp>(middle, end, less);
	Container buffer = merge<Container, Itr, Cmp>(begin, middle, end, less);

	std::move(buffer.cbegin(), buffer.cend(), begin);
}

//------------------------------------------------------------------------------

};	// namespace

#endif /*_RAMPAGE_SORTING_MERGESORT_H_*/
