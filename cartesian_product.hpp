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

template <typename... Ranges>
class cartesian_product_iterator : public std::iterator<
  // iterator_category
  std::iterator_traits<get_type_t<0, typename Ranges::const_iterator...>>::iterator_category,
  // T
  std::tuple<typename std::iterator_traits<typename Ranges::const_iterator>::reference...>,
  // difference_type
  typename std::iterator_traits<get_type_t<0, typename Ranges::const_iterator...>>::difference_type,
  // T *
  const std::tuple<typename std::iterator_traits<typename Ranges::const_iterator>::reference...> *,
  // T &
  const std::tuple<typename std::iterator_traits<typename Ranges::const_iterator>::reference...> &
  > {
public:
  cartesian_product_iterator(BeginIteratorRef<Ranges const>... ranges) :
    iterators_ {std::make_tuple(ranges.get().begin()...)},
    begins_ {std::make_tuple(ranges.get().begin()...)},
    ends_ {std::make_tuple(ranges.get().end()...)} {}

    cartesian_product_iterator(BeginIteratorRef<Ranges const>... ranges) :
      iterators_ {std::make_tuple(ranges.get().begin()...)},
      begins_ {std::make_tuple(ranges.get().begin()...)},
      ends_ {std::make_tuple(ranges.get().end()...)} {
        std::get<0>(iterators_) = get_value<0>(ranges.get()...).end();
      }

      cartesian_product_iterator operator++() {
        advance_cartesian(iterators_, begins_, ends_);
        return *this;
      }

      auto operator*() {
        return transform_tuple(iterators_, [](auto const & iterator) {
          return *iterator;
        });
      }

      bool operator==(cartesian_product_iterator const & other) {
        return iterators_ == other.iterators_;
      }

      bool operator!=(cartesian_product_iterator const & other) {
        return !(*this == other);
      }

      auto operator-(cartesian_product_iterator const & other) {
        return distance_cartesan(other.iterators_, iterators_, begins_, ends_);
      }


private:
  std::tuple<typename Ranges::const_iterator...> iterators_;
  std::tuple<typename Ranges::const_iterator...> begins_;
  std::tuple<typename Ranges::const_iterator...> ends_;
};

namespace view {

template <typename... Ranges>
auto cartesian_product(Ranges const &... ranges) {
  return iterator_range<cartesian_product_iterator<
      typename Ranges::const_iterator...>>(
      cartesian_product_iterator(BeginIteratorRef<Ranges const>(ranges)...),
      cartesian_product_iterator(EndIteratorRef<Ranges const>(ranges)...)
      );
}

} // namespace view
} //namespace ranges

#endif /* CARTESIAN_PRODUCT_HPP_ */
