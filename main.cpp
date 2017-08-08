#include "iterator_range.hpp"
#include "algorithm.hpp"
#include "transform.hpp"
#include "variadic.hpp"
#include <iostream>
#include <vector>

int multiplyBy2(int i) { return i * 2; }
bool testTransform() {
  std::vector<int> input = {1, 2, 3, 4, 5};
  std::vector<int> expected = {2, 4, 6, 8,10};
  std::vector<int> result;
  // type of doubledNumbers will be
  // iterator_range<transform_iterator<input's const_iterator, multiplyByTwo>>
  auto doubledNumbers = input | ranges::view::transform(multiplyBy2);
  ranges::push_back(result, doubledNumbers);
  return result == expected;
}

// if function has to be taken as universal reference
// but what is the need?
//template <typename FuncT>
//bool testResult(FuncT && function) {
//  return std::forward<FuncT>(function)();
//}

template <typename FuncT>
bool testResult(FuncT function) {
  return function();
}

void launchTests() {
  std::cout << "testResult(testTransform): "
      << std::boolalpha
      << testResult(testTransform) << std::endl;

}

int main() {
  std::cout << std::boolalpha << is_const_iterator<const int *>::value << std::endl;
  launchTests();
  return 0;
}
