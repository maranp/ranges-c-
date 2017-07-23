#ifndef ITERATOR_RANGE_HPP
#define ITERATOR_RANGE_HPP

#include <type_traits>
#include <iterator>

template <typename Iterator>
struct is_const_iterator {
  static const bool value = std::is_const<
                               typename std::remove_reference<
				 typename std::iterator_traits<
				   Iterator
				   >::reference
				 >::type
                            >::value;
};

template <bool is_const_iterator_range, typename Iterator>
struct iterator_range_impl {
public:
  iterator_range_impl(Iterator begin, Iterator end) :
    begin_ {begin}, end_ {end} {}
    
  Iterator begin() const {
    return begin_;
  }
  Iterator end() const {
    return end_;
  }

  typename std::iterator_traits<Iterator>::difference_type const size() const {
    return end_ - begin_;
  }
  
  using const_iterator = Iterator;

private:
  Iterator begin_;
  Iterator end_;
};

template <typename Iterator>
struct iterator_range_impl<false, Iterator> {
public:
  iterator_range_impl(Iterator begin, Iterator end) :
    begin_ {begin}, end_ {end} {}
    
  Iterator begin() const {
    return begin_;
  }
  Iterator end() const {
    return end_;
  }

  typename std::iterator_traits<Iterator>::difference_type const size() const {
    return end_ - begin_;
  }

  using iterator = Iterator;

private:
  Iterator begin_;
  Iterator end_;
};

template <typename Iterator>
struct iterator_range : public iterator_range_impl<is_const_iterator<Iterator>::value, Iterator> {
  using base = iterator_range_impl<is_const_iterator<Iterator>::value, Iterator>;

  iterator_range(Iterator begin, Iterator end) : base(begin, end) {}
};

#endif // ITERATOR_RANGE_HPP
