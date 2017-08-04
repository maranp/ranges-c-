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
template <typename DstRange, typename SrcRange>
void push_back(DstRange & dst, SrcRange const & src) {
  std::copy(src.begin(), src.end(), std::back_inserter(dst));
}
} //namespace ranges



#endif /* ALGORITHM_HPP_ */
