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

completor::internal_trie::iterator completor::find_next_(
    const completor::internal_trie::iterator& iter, std::string& word) {
  if (iter.is_leaf()) {
    return _storage.end();
  }
  std::pair<size_t, size_t> best = { -1, 0 };
  for (size_t key = _min_key; key <= _max_key; ++key) {
    const auto ans = iter[key];
    if (ans != _storage.end() && best.first < (*ans).first) {
      best.first = (*ans).first;
      best.second = key;
    }
  }
  word += char(best.second);
  return iter[best.second];
}

void completor::add_over_(const std::string& word) {
  auto it = _storage.begin();
  std::for_each(word.begin(), word.end(), [](char ch) {
    ++(*it)->first;
    (*it).second;
    it = it[ch];
  });
}

std::string completor::complete(std::string word) {
  auto it = _storage.find_prefix(word);
  if (it == _storage.end()) {
    return "";
  }
  do {
    it = find_next_(it, word);
    
  } while (true);
}

}  // namespace solver
