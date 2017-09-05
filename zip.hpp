/*
 * zip.hpp
 *
 *  Created on: 05-Sep-2017
 *      Author: maran
 */

#ifndef ZIP_HPP_
#define ZIP_HPP_

#include "variadic.hpp"

namespace ranges {

namespace view {

template <typename... UnderlyingIterators>
class zip_iterator : public std::iterator<
  typename std::iterator_traits<get_type_t<0, UnderlyingIterators...>>::iterator_category,
  std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...>,
  typename std::iterator_traits<get_type_t<0, UnderlyingIterators...>>::difference_type,
  const std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...> *,
  const std::tuple<typename std::iterator_traits<UnderlyingIterators>::reference...> &
> {
public:
  zip_iterator(UnderlyingIterators... iterators) : iterators_ {std::make_tuple(iterators...)} {}
  zip_iterator operator++() {
    for_each_tuple(iteratos_, [](auto &iterator) {
      iterator++;
    });
    return *this;
  }
  zip_iterator operator--() {
    for_each_tuple(iteratos_, [](auto &iterator) {
      iterator--;
    });
    return *this;
  }
  zip_iterator& operator=(zip_iterator const & it) {
    iteratos_ = it;
    return *this;
  }


private:
    std::tuple<UnderlyingIterators...> iteratos_;
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

}
}



#endif /* ZIP_HPP_ */
