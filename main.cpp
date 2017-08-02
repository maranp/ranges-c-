#include "iterator_range.hpp"
#include <iostream>
#include <vector>

bool testTransform() {
  std::vector<int> input = {1, 2, 3, 4, 5};
  std::vector<int> expected = {2, 4, 6, 8,10};
  std::vector<int> result;
  return true;
}

template <typename FuncT>
bool testResult(FuncT && function) {
  return std::forward<FuncT>(function)();
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
