#include "iterator_range.hpp"
#include <iostream>

int main() {
  std::cout << is_const_iterator<const int *>::value << std::endl;
  return 0;
}
