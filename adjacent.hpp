/*
 * adjacent.hpp
 *
 *  Created on: 18-Sep-2017
 *      Author: maran
 */

#ifndef ADJACENT_HPP_
#define ADJACENT_HPP_

#include "iterator_range.hpp"
#include "named_type.hpp"
#include <iterator>
#include <utility>

namespace ranges {

template <typename Iterator>
using BeginIterator = NamedType<Iterator, struct begin_context>;

template <typename Iterator>
using EndIterator = NamedType<Iterator, struct end_context>;

template <typename UnderlyingIterator>
class adjacent_iterator : public std::iterator <
  // iterator category
  typename std::iterator_traits<UnderlyingIterator>::iterator_category,
  // type
  std::pair<typename std::iterator_traits<UnderlyingIterator>::value_type, typename std::iterator_traits<UnderlyingIterator>::value_type>,
  // difference_type
  typename std::iterator_traits<UnderlyingIterator>::difference_type,
  // T *
  const std::pair<typename std::iterator_traits<UnderlyingIterator>::value_type, typename std::iterator_traits<UnderlyingIterator>::value_type> *,
  // T &
  const std::pair<typename std::iterator_traits<UnderlyingIterator>::value_type, typename std::iterator_traits<UnderlyingIterator>::value_type> &
> {
public:
  explicit adjacent_iterator(BeginIterator<UnderlyingIterator> begin, EndIterator<UnderlyingIterator> end)
      : iterator_ {begin.get()},
        next_ { begin.get() != end.get() ? std::next(begin.get()) : begin.get() },
        isEnd_ { false } {}

  explicit adjacent_iterator(EndIterator<UnderlyingIterator> end)
      : iterator_ {end.get()}, next_ { end.get() }, isEnd_ { true } {}

  auto operator++() {
    iterator_++; next_++;
    return *this;
  }

  auto operator*() {
    return std::make_pair(*iterator_, *next_);
  }

  bool operator==(adjacent_iterator const & other) {
    if (isEnd_ == other.isEnd_) {
      return iterator_ == other.iterator_;
    }
    if (other.isEnd_) {
      return next_ == other.iterator_;
    }
    if (isEnd_) {
      return iterator_ == other.next_;
    }
  }

  bool operator!=(adjacent_iterator const & other) {
    return !(*this == other);
  }

  auto operator-(adjacent_iterator const & other) {
    return next_ - other.next_;
  }

private:
  UnderlyingIterator iterator_;
  UnderlyingIterator next_;
  bool isEnd_;

};

namespace view {

template <typename Range>
auto consecutive(Range & range) -> iterator_range<adjacent_iterator<decltype(range.begin())>> {
  using UnderlyingIterator = decltype(range.begin());
  return iterator_range<adjacent_iterator<UnderlyingIterator>>(
          adjacent_iterator<UnderlyingIterator>(BeginIterator<UnderlyingIterator>(range.begin()), EndIterator<UnderlyingIterator>(range.end())),
          adjacent_iterator<UnderlyingIterator>(EndIterator<UnderlyingIterator>(range.end())));
}
struct adjacent_adaptor {};
adjacent_adaptor adjacent;

template <typename Range>
auto operator |(Range & range, adjacent_adaptor) -> iterator_range<adjacent_iterator<decltype(range.begin())>> {
  return consecutive(range);
}

} // namespace view
} // namespace ranges

#endif /* ADJACENT_HPP_ */
