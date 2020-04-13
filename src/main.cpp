#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "completor.hpp"

std::vector<std::string> read_words() {
  size_t count;
  std::cin >> count;
  std::vector<std::string> words(count);
  std::for_each(words.begin(), words.end(), [&](std::string& word) {
    std::cin >> word;
  });
  return words;
}

void answer_queries() {
  solver::completor completor(read_words());
  size_t count;
  std::cin >> count;
  for (size_t i = 0; i < count; ++i) {
    std::string s;
    std::cin >> s;
    std::cout << completor.complete(s) << '\n';
  }
}

int main() {
  answer_queries();
}
