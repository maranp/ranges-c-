/*
 * named_type.hpp
 *
 *  Created on: 11-Aug-2017
 *      Author: maran
 */

#ifndef NAMED_TYPE_HPP_
#define NAMED_TYPE_HPP_

#include <functional>

// a phantom type is a type which is not used in the
// implementation but just used to differentiate
// instationation of 2 named types if the underlying
// T is same type.
// For example if width and height are represented as double
// declaring (using) width and height as NamedType<double>
// will result in same type. To differentiate between
// double typed width and height, a phatom type is used
// usage:
// using Width = NamedType<double, struct WidthParam>;
// using Height = NamedType<double, struct HeightParam>;
// Rectangle r {Width {10}, Height {20}};
// http://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
template <typename T, typename PhantomType>
class NamedType {
public:
  NamedType(T const & value_) : value {value_} {} // lvalue reference param
  NamedType(T && value_) : value {std::move(value)} {} // rvalue ref param
  T & get() { return value; }
  T const & get() const { return value; }
private:
  T value;
};

template <typename T, typename PhantomType>
class NamedTypeRef {
public:
  NamedTypeRef(T & value) : tref {std::ref(value)} {}
  T & get() { return tref.get(); }
  T const & get() const { return tref.get(); }
private:
  // to strore a reference in a copyiable/assignable object
  // get return the reference being stored
  std::reference_wrapper<T> tref;
};

#endif /* NAMED_TYPE_HPP_ */
