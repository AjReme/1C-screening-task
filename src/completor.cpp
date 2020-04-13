#include <vector>
#include <string>
#include <algorithm>

#include "completor.hpp"

namespace solver {

completor::completor() {
}

completor::completor(const std::vector<std::string>& init_vec) {
  std::for_each(init_vec.begin(), init_vec.end(),
                [this](const std::string& word) { insert(word); });
}

void completor::insert(const std::string& word) {
  _storage.insert(word);
}

completor::internal_trie::iterator completor::find_next_lex_min_(
    const completor::internal_trie::iterator& iter, std::string& word) {
  for (size_t key = _min_key; key <= _max_key; ++key) {
    const auto ans = iter[key];
    if (ans != _storage.end()) {
      word += char(key);
      return ans;
    }
  }
  return _storage.end();
}

std::string completor::complete(const std::string& word) {
  auto it = _storage.find_prefix(word);
  std::string ret = word;
  do {
    if (it.is_leaf()) {
      return ret;
    }
    it = find_next_lex_min_(it, ret);
    if (it == _storage.end()) {
      return "";
    }
  } while (true);
}

}  // namespace solver
