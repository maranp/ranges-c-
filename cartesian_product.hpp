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
#include "named_type.hpp"

namespace ranges {
// BeginIteratorRef is a reference type (std::reference_wrapper)
// that holds the reference to iterator being distinguished as
// begin iterator
template <typename Range>
using BeginIteratorRef = NamedTypeRef<Range, struct begin_context>;

template <typename Range>
using EndIteratorRef = NamedTypeRef<Range, struct end_context>;

namespace view {

template <typename... Ranges>
auto cartesian_product(Ranges const &... ranges) {
  return iterator_range<cartesian_product_iterator<
      typename Ranges::const_iterator...>>(
      make_cartesian_product_iterator(BeginIteratorRef<Ranges const>(ranges)...),
      make_cartesian_product_iterator(EndIteratorRef<Ranges const>(ranges)...)
      );
}

} // namespace view
} //namespace ranges

#endif /* CARTESIAN_PRODUCT_HPP_ */
