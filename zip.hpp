/*
 * zip.hpp
 *
 *  Created on: 05-Sep-2017
 *      Author: maran
 */

#ifndef ZIP_HPP_
#define ZIP_HPP_

/*
 * zips
 * {a, b}
 * {1, 2, 3},
 * {X, Y, Z}
 * into a view of
 * {
 * std::tuple(a, 1, X}
 * std::tuple(b, 2, Y}
 * }
 */

#include "variadic.hpp"

namespace ranges {

namespace view {

template <typename... UnderlyingIterators>
class zip_iterator : public std::iterator<
  // iterator category
  typename std::iterator_traits<get_type_t<0, UnderlyingIterators...>>::iterator_category,
  // T - type of the elements in the range iterated by the zip-iterator
  std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...>,
  // difference_type of any of the iterator in underlying iterators
  typename std::iterator_traits<get_type_t<0, UnderlyingIterators...>>::difference_type,
  // T *
  const std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...> *,
  // T &
  const std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...> &
> {
public:
  zip_iterator(UnderlyingIterators... iterators) : iterators_ {std::make_tuple(iterators...)} {}
  zip_iterator operator++() {
    for_each_in_tuple(iterators_, [](auto &iterator) {
      iterator++;
    });
    return *this;
  }
  zip_iterator operator--() {
    for_each_in_tuple(iterators_, [](auto &iterator) {
      iterator--;
    });
    return *this;
  }
  zip_iterator& operator=(zip_iterator const & it) {
    iterators_ = it;
    return *this;
  }

  auto operator*() {
    return transform_tuple(iterators_, [](auto const &it) {
      return *it;
    });
  }

  bool operator==(zip_iterator const &other) {
    return iterators_ == other.iterators_;
  }

  bool operator!=(zip_iterator const &other) {
    return !(*this == other);
  }

  auto operator-(zip_iterator const &other) {
    return std::get<0>(iterators_) - std::get<0>(other.iterators_);
  }


private:
    std::tuple<UnderlyingIterators...> iterators_;
};

template <typename... UnderlyingIterators>
zip_iterator<UnderlyingIterators...> make_zip_iterator(UnderlyingIterators... iterators) {
  return zip_iterator<UnderlyingIterators...>(iterators...);
}

// zip function returns an iterator_range which provides a view of a range of
// elements where each element is a tuple of elements which are elements of corresponding
// position in the given ranges.
template <typename... Ranges>
iterator_range<zip_iterator<typename Ranges::const_iterator...>> zip(Ranges const&... ranges) {
  return iterator_range<zip_iterator<typename Ranges::const_iterator...>>(
      make_zip_iterator(ranges.begin()...),
      make_zip_iterator(ranges.end()...));
}

} // namespace view
} // namespace ranges



#endif /* ZIP_HPP_ */
