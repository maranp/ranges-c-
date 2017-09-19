#include "iterator_range.hpp"
#include "algorithm.hpp"
#include "transform.hpp"
#include "variadic.hpp"
#include "zip.hpp"
#include "cartesian_product.hpp"
#include "adjacent.hpp"
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

std::string letterToNext(char first, char second) {
  std::ostringstream oss;
  oss << first << "-" << second;
  return oss.str();
}

bool testZip() {
  std::vector<char> input1 = {'A', 'B', 'C', 'D', 'E'};
  std::vector<int> input2 = {1, 2, 3, 4, 5};
  std::vector<std::string> expected = {"A1", "B2", "C3", "D4", "E5"};

  std::vector<std::string> result;

  ranges::push_back(result,
                    ranges::view::zip(input1, input2)
                    | ranges::view::transform(tupled_args(letterPlusNumber)));

  return result == expected;
}

bool testCartesian() {
  std::vector<char> input1 = {'A', 'B', 'C', 'D', 'E'};
  std::vector<int> input2 = {1, 2, 3, 4, 5};
  std::vector<std::string> expected = {"A1", "A2", "A3", "A4", "A5",
                                       "B1", "B2", "B3", "B4", "B5",
                                       "C1", "C2", "C3", "C4", "C5",
                                       "D1", "D2", "D3", "D4", "D5",
                                       "E1", "E2", "E3", "E4", "E5" };

  std::vector<std::string> result;

  ranges::push_back(result,
                    ranges::view::cartesian_product(input1, input2)
                    | ranges::view::transform(tupled_args(letterPlusNumber)));

  for (auto x : result) {
    std::cout << x << std::endl;
  }
  return result == expected;
}

bool testAdjacent() {
  std::vector<char> input = {'A', 'B', 'C', 'D', 'E', 'F'};
  std::vector<std::string> expected = {"A-B", "B-C", "C-D", "D-E", "E-F"};

  std::vector<std::string> result;

  push_back(result,
                    input | ranges::view::adjacent
                    | ranges::view::transform(paired_args(letterToNext)));

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
  std::cout << "testResult(testZip): "
      << std::boolalpha
      << testResult(testZip) << std::endl;
  std::cout << "testResult(testCartesian): "
      << std::boolalpha
      << testResult(testCartesian) << std::endl;
  std::cout << "testResult(testAdjacent): "
      << std::boolalpha
      << testResult(testAdjacent) << std::endl;
}

int main() {
  std::cout << std::boolalpha << is_const_iterator<const int *>::value << std::endl;
  launchTests();
  return 0;
}
