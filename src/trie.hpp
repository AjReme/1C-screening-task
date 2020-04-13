#include <vector>
#include <iterator>
#include <algorithm>

namespace data_structure {

template <size_t min_key, size_t max_key, class value>
class trie {
 private:
  static const size_t _block_size = max_key - min_key + 1;

  struct node_t {
    value val;
    bool is_leaf;
    size_t in_route = 0;
    std::vector<node_t*> child;

    node_t()
        : val(value()),
          is_leaf(false),
          in_route(0),
          child(std::vector<node_t*>(_block_size, nullptr)) {
    }

    ~node_t() {
      std::for_each(child.begin(), child.end(),
                    [](const node_t* ptr) { delete ptr; });
    }
  };

  node_t* _root;

  template <class ForwardIt>
  node_t* find_(const ForwardIt first, const ForwardIt last) const {
    using iter_type = typename std::iterator_traits<ForwardIt>::value_type;
    node_t* ptr = _root;
    std::find_if(first, last, [&ptr](const iter_type& val) {
      ptr = ptr->child[val - min_key];
      return ptr == nullptr;
    });
    return ptr;
  }

 public:
  class iterator {
   private:
    node_t* _ptr;

   public:
    iterator() : _ptr(nullptr) {
    }

    iterator(node_t* const ptr) : _ptr(ptr) {
    }

    iterator& operator=(const iterator& other) {
      _ptr = other._ptr;
      return *this;
    }

    bool operator==(const iterator& other) const {
      return _ptr == other._ptr;
    }

    bool operator!=(const iterator& other) const {
      return _ptr != other._ptr;
    }

    iterator operator[](const size_t& next) const {
      return iterator(_ptr == nullptr ? _ptr : _ptr->child[next - min_key]);
    }

    value& operator*() const {
      return _ptr->val;
    }

    bool is_leaf() const {
      return _ptr == nullptr ? false : _ptr->is_leaf;
    }
  };

  trie() : _root(new node_t()) {
  }

  trie(trie<min_key, max_key, value>&& other) {
    clear();
    _root = other._root;
    other._root = new node_t();
  }

  ~trie() {
    delete _root;
  }

  size_t size() const {
    return _root->in_route;
  }

  bool empty() const {
    return _root->in_route == 0;
  }

  void clear() {
    delete _root;
    _root = new node_t();
  }

  iterator begin() const {
    return iterator(_root);
  }

  const iterator end() const {
    return iterator();
  }

  template <class ForwardIt>
  iterator insert(const ForwardIt first, const ForwardIt last) {
    using iter_type = typename std::iterator_traits<ForwardIt>::value_type;
    node_t* ptr = _root;
    std::for_each(first, last, [&ptr](const iter_type& val) {
      node_t*& next = ptr->child[val - min_key];
      if (next == nullptr) {
        next = new node_t();
      }
      ptr = next;
    });
    if (ptr->is_leaf) {
      return iterator(ptr);
    }
    ptr = _root;
    ++ptr->in_route;
    std::for_each(first, last, [&ptr](const iter_type& val) {
      ptr = ptr->child[val - min_key];
      ++ptr->in_route;
    });
    ptr->is_leaf = true;
    return iterator(ptr);
  }

  template <class Iterable>
  iterator insert(const Iterable& container) {
    return insert(container.begin(), container.end());
  }

  template <class Iterable>
  value& operator[](const Iterable& container) {
    return *insert(container);
  }

  template <class ForwardIt>
  void erase(const ForwardIt first, const ForwardIt last) {
    using iter_type = typename std::iterator_traits<ForwardIt>::value_type;
    node_t* ptr = _root;
    --ptr->in_route;
    std::find_if(first, last, [&ptr](const iter_type& val) {
      ptr = ptr->child[val - min_key];
      if (--ptr->in_route == 0) {
        delete ptr;
        ptr = nullptr;
        return true;
      }
      return false;
    });
    if (ptr != nullptr) {
      ptr->is_leaf = false;
    }
  }

  template <class Iterable>
  iterator erase(const Iterable& container) {
    return erase(container.begin(), container.end());
  }

  template <class Iterable>
  iterator find(const Iterable& container) const {
    node_t* ret = find_(container.begin(), container.end());
    return iterator(ret != nullptr && ret->is_leaf ? ret : nullptr);
  }

  template <class Iterable>
  iterator find_prefix(const Iterable& container) const {
    node_t* ret = find_(container.begin(), container.end());
    return iterator(ret != nullptr ? ret : nullptr);
  }
};

}  // namespace data_structure
