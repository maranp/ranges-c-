#ifndef ITERATOR_RANGE_HPP
#define ITERATOR_RANGE_HPP

#include <type_traits>
#include <iterator>

// http://en.cppreference.com/w/cpp/iterator/iterator_traits
// const T* specialization member types
// value_type   T
// reference  const T&
// difference_type  std::ptrdiff_t
template <typename Iterator>
struct is_const_iterator {
  static const bool value = std::is_const<
      typename std::remove_reference<
        typename std::iterator_traits<Iterator>::reference
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

// we have the iterator type as type parameter.
// we want to send whether the iterator is const or not to the base class type parameter
// std::is_const is a struct which takes its parameter type as the type whose const need to be identified
// so, we can directly pass is_const<Iterator>::value to base class type param.
// But we are not worried whether Iterator is const. We only care about the constness of underlying type that iterator
// points to. We could think Iterator::value_type can be passed to is_const. But Iterator::value_type just provides
// the type and not the constness. std::iterator_traits<Iterator>::reference gives const T & if underlying type has const
// so we need to take std::iterator_traits<Iterator>::reference and then apply std::remove_reference<> on it
// so what we really want is, std::is_const<std::remove_reference<std::iterator_traits<Iterator>::reference>::type>::value
// which is quite complicated. so, a convenience wrapper struct called is_const_iterator<Iterator>::value returns the
// same logic
template <typename Iterator>
struct iterator_range :
    public iterator_range_impl<is_const_iterator<Iterator>::value, Iterator> {
  using base = iterator_range_impl<is_const_iterator<Iterator>::value, Iterator>;

  iterator_range(Iterator begin, Iterator end) : base(begin, end) {}
};

#endif // ITERATOR_RANGE_HPP
