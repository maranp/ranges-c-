#include "iterator_range.hpp"
#include "algorithm.hpp"
#include "transform.hpp"
#include "variadic.hpp"
#include "zip.hpp"
#include <iostream>
#include <vector>
#include <sstream>

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

std::string letterPlusNumber(char line, int column) {
  std::ostringstream pos;
  pos << line << column;
  return pos.str();
}

bool testZip() {
  std::vector<char> input1 = {'A', 'B', 'C', 'D', 'E'};
  std::vector<int> input2 = {1, 2, 3, 4, 5};
  std::vector<std::string> expected = {"A1", "B2", "C3", "D4", "E5"};

  std::vector<std::string> result;

  ranges::push_back(result,
                    ranges::view::zip(input1, input2)
                    | ranges::view::transform(tupled_args(letterPlusNumber)));

  for (auto x : result) {
    std::cout << x << std::endl;
  }
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
  std::cout << "testResult(testTransform): "
      << std::boolalpha
      << testResult(testZip) << std::endl;
}

int main() {
  std::cout << std::boolalpha << is_const_iterator<const int *>::value << std::endl;
  launchTests();
  return 0;
}
