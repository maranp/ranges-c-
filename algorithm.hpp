/*
 * algorithm.hpp
 *
 *  Created on: 04-Aug-2017
 *      Author: maran
 */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <algorithm>

namespace ranges {
template <typename SrcRange, typename Iterator>
Iterator copy(SrcRange const & src, Iterator dst) {
  return std::copy(src.begin(), src.end(), dst);
}

// though range is declared const, for_each might mutate the elements
// pointed by iterator of the range.
// const range just means the begin and end iterators are not mutable and not the elements they point to
// what is the purpose of returning Func?
// Fuct need not be a func,tion. it could be a function object.
// The function object could well be tracking the result (effect) of calling func so far
// (via a memeber of function object)
// and once for_each returns the func, the caller could retrieve the effect of func from the member
// for concrete example, look at the example here http://en.cppreference.com/w/cpp/algorithm/for_each
template <typename Range, typename Func>
Func for_each(Range const & range, Func func) {
  return std::for_each(range.begin(), range.end(), func);
}

template <typename DstRange, typename SrcRange>
void push_back(DstRange & dst, SrcRange const & src) {
  copy(src, std::back_inserter(dst));
}
} //namespace ranges



#endif /* ALGORITHM_HPP_ */
