/*
 * cartesian.hpp
 *
 *  Created on: 13-Sep-2017
 *      Author: maran
 */

#ifndef CARTESIAN_PRODUCT_HPP_
#define CARTESIAN_PRODUCT_HPP_

#include "iterator_range.hpp"
#include "variadic.hpp"

namespace ranges {

namespace view {

template <typename... Ranges>
auto cartesian_product(Ranges const &... ranges) {
  return iterator_range<cartesian_product_iterator<typename Ranges::const_iterator...>>(
      make_cartesian_product_iterator(ranges.begin()...),
      make_cartesian_product_iterator(ranges.end()...)
      );
}

} // namespace view
} //namespace ranges

#endif /* CARTESIAN_PRODUCT_HPP_ */
