/*
 * transform.hpp
 *
 *  Created on: 04-Aug-2017
 *      Author: maran
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

namespace ranges {
// a standard iterator with specific features
// takes standard iterator and a function
// when dereferenced, applies the function and then returns the value
template <typename Iterator, typename FuncT>
struct transform_iterator : public std::iterator<
  typename std::iterator_traits<Iterator>::iterator_category,
  std::result_of_t<FuncT(typename std::iterator_traits<Iterator>::value_type)>,
  typename std::iterator_traits<Iterator>::difference_type,
  const std::result_of_t<FuncT(typename std::iterator_traits<Iterator>::value_type)>*,
  const std::result_of_t<FuncT(typename std::iterator_traits<Iterator>::value_type)>&
  > {
  transform_iterator(Iterator iterator, FuncT func) : iterator_ {iterator}, func_ {func} {}
  auto operator*() {
    return func_(*iterator_);
  }
  transform_iterator<Iterator, FuncT> & operator=(transform_iterator<Iterator, FuncT> const &rhs) {
    iterator_ = rhs.iterator_;
    func_ = rhs.func_;
    return *this;
  }
  transform_iterator<Iterator, FuncT> & operator++() {
    ++iterator_;
    return *this;
  }
  bool operator==(transform_iterator<Iterator, FuncT> const & rhs) {
    return iterator_ == rhs.iterator_;
  }
  bool operator!=(transform_iterator<Iterator, FuncT> const & rhs) {
    return !(rhs == *this);
  }
  auto operator-(transform_iterator<Iterator, FuncT> const & rhs) {
    return iterator_ - rhs.iterator_;
  }
private:
  Iterator iterator_;
  FuncT func_;
};

template <typename Iterator, typename FuncT>
transform_iterator<Iterator, FuncT> make_transform_iterator(Iterator iterator,
                                                           FuncT func) {
  return transform_iterator<Iterator, FuncT>(iterator, func);
}
namespace view {
template <typename FuncT>
struct transform_adaptor {
  explicit transform_adaptor(FuncT func) : func_ {func} {}
  FuncT getFunction() const {return func_;}
private:
  FuncT func_;
};

template <typename FuncT>
transform_adaptor<FuncT> transform(FuncT func) {
  return transform_adaptor<FuncT>(func);
}

// we want to "pipe" a container (range) to a "transformer"
// to a get a view of range thats result of applying transformation on the container
// the transformer which is called adaptor is one just stores the transforming function object
// its not clean why an adaptor (a storage for function object) is needed at all
template <typename Range, typename FuncT>
iterator_range<
  transform_iterator<typename Range::const_iterator, FuncT>>
  operator|(Range const & range, transform_adaptor<FuncT> adaptor) {
  return iterator_range<
    transform_iterator<typename Range::const_iterator, FuncT>
    >(make_transform_iterator(range.begin(), adaptor.getFunction()),
      make_transform_iterator(range.end(), adaptor.getFunction()));
}

} // namespace view

} // namespace ranges



#endif /* TRANSFORM_HPP_ */
