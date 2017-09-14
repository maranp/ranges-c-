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

template <size_t n, typename... Iterators>
struct Advance_cartesan_impl {
  void operator()(std::tuple<Iterators...> &iterators,
      std::tuple<Iterators...> const &begins,
      std::tuple<Iterators...> const &ends) {

    ++std::get<n>(iterators);
    if (std::get<n>(iterators) == std::get<n>(ends)) {
      std::get<n>(iterators) = std::get<n>(begins);
      Advance_cartesan_impl<n -1, Iterators...>()(iterators, begins, ends);
    }
  }
};

template <typename... Iterators>
struct Advance_cartesan_impl<0, Iterators...> {
  void operator()(std::tuple<Iterators...> &iterators,
        std::tuple<Iterators...> const &,
        std::tuple<Iterators...> const &) {

      ++std::get<0>(iterators);
    }
};

template <typename... Iterators>
void advance_cartesan(std::tuple<Iterators...> &iterators,
    std::tuple<Iterators...> const &begins,
    std::tuple<Iterators...> const &ends) {
  Advance_cartesan_impl<sizeof...(Iterators) - 1, Iterators...>()(
      iterators, begins, ends);
}

template <size_t n, typename... Iterators>
struct Distance_cartesan_impl {
  size_t operator()(std::tuple<Iterators...> const &iterators1,
    std::tuple<Iterators...> const &iterators2,
    std::tuple<Iterators...> const &begins,
    std::tuple<Iterators...> const &ends) {
    return Distance_cartesan_impl<n - 1, Iterators...>()(
        iterators1, iterators2, begins, ends)
        * (std::get<n>(ends) - std::get<n>(begins))
        + std::get<n>(iterators2) - std::get<n>(iterators1);
  }
};

template <typename... Iterators>
struct Distance_cartesan_impl<0, Iterators...> {
  size_t operator()(std::tuple<Iterators...> const &iterators1,
    std::tuple<Iterators...> const &iterators2,
    std::tuple<Iterators...> const &,
    std::tuple<Iterators...> const &) {
    return std::get<0>(iterators2) - std::get<0>(iterators1);
  }
};

template <typename... Iterators>
size_t distance_cartesan(std::tuple<Iterators...> const &iterators1,
    std::tuple<Iterators...> const &iterators2,
    std::tuple<Iterators...> const &begins,
    std::tuple<Iterators...> const &ends) {
  return Distance_cartesan_impl<sizeof...(Iterators) - 1, Iterators...>()(
      iterators1, iterators2, begins, ends);
}

template <typename... Ranges>
class cartesian_product_iterator : public std::iterator<
  // iterator_category
  typename std::iterator_traits<get_type_t<0, typename Ranges::const_iterator...>>::iterator_category,
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

    cartesian_product_iterator(EndIteratorRef<Ranges const>... ranges) :
      iterators_ {std::make_tuple(ranges.get().begin()...)},
      begins_ {std::make_tuple(ranges.get().begin()...)},
      ends_ {std::make_tuple(ranges.get().end()...)} {
        std::get<0>(iterators_) = get_value<0>(ranges.get()...).end();
      }

      cartesian_product_iterator operator++() {
        advance_cartesan(iterators_, begins_, ends_);
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

      size_t operator-(cartesian_product_iterator const & other) {
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
  return iterator_range<cartesian_product_iterator<Ranges...>>(
      cartesian_product_iterator<Ranges...>(BeginIteratorRef<Ranges const>(ranges)...),
      cartesian_product_iterator<Ranges...>(EndIteratorRef<Ranges const>(ranges)...)
      );
}

} // namespace view
} //namespace ranges

#endif /* CARTESIAN_PRODUCT_HPP_ */
