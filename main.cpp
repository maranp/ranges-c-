#include "iterator_range.hpp"
#include "algorithm.hpp"
#include <iostream>
#include <vector>

bool testTransform() {
  std::vector<int> input = {1, 2, 3, 4, 5};
  std::vector<int> expected = {2, 4, 6, 8,10};
  std::vector<int> result;
  auto doubledNumbers = input | ranges::view::transform(multiplyByTwo);
  ranges::push_back(result, doubledNumbers);
  return true;
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
