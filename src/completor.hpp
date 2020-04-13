#include <limits>
#include <vector>
#include <string>

#include "trie.hpp"

namespace solver {

class completor {
 private:
  static const size_t _min_key = 'a';
  static const size_t _max_key = 'z';

  using internal_trie = data_structure::trie<_min_key, _max_key, size_t>;

  internal_trie _storage;

  internal_trie::iterator find_next_lex_min_(
      const internal_trie::iterator& iter, std::string& word);

 public:
  completor();

  completor(const std::vector<std::string>& init_vec);

  void insert(const std::string& word);

  std::string complete(const std::string& word);
};

}  // namespace solver
