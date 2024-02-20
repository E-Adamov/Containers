#ifndef CPP2_S21_CONTAINERS_SRC_S21_MULTISET__H_
#define CPP2_S21_CONTAINERS_SRC_S21_MULTISET__H_

#include <cstddef>           // для std::size_t
#include <initializer_list>  // для std::initializer_list
#include <utility>           // для std::pair

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class multiset : RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21::RBTree<key_type, value_type>::iterator;
  using const_iterator =
      typename s21::RBTree<key_type, value_type>::const_iterator;
  using size_type = std::size_t;

  typedef s21::RBTreeNode<key_type, value_type> Node;

  multiset(){};
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset(){};
  multiset operator=(multiset &&ms);

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const_reference value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  size_type count(const_reference key);
  iterator find(const_reference key);
  bool contains(const_reference key);
  std::pair<iterator, iterator> equal_range(const_reference key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  size_type size_{0};
  using s21::RBTree<key_type, value_type>::_root;
  using s21::RBTree<key_type, value_type>::Contains;
  using s21::RBTree<key_type, value_type>::Insert;
  using s21::RBTree<key_type, value_type>::Remove;
};

template <class value_type>
s21::multiset<value_type>::multiset(
    const std::initializer_list<value_type> &items) {
  for (auto item : items) {
    insert(item);
  }
}

template <class value_type>
s21::multiset<value_type>::multiset(const s21::multiset<value_type> &ms) {
  iterator it = ms.begin();
  iterator it_end = ms.end();
  while (it != it_end) {
    insert(*it);
    ++it;
  }
}

template <class value_type>
s21::multiset<value_type>::multiset(s21::multiset<value_type> &&ms) {
  clear();
  swap(ms);
}

template <class value_type>
s21::multiset<value_type> s21::multiset<value_type>::operator=(
    s21::multiset<value_type> &&ms) {
  clear();
  swap(ms);
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::insert(
    const_reference value) {
  Insert(value, value);
  ++size_;
  iterator result = find(value);
  return result;
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::begin()
    const {
  Node *x = _root;
  while (x->_left) x = x->_left;
  return iterator(_root, x);
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::end()
    const {
  Node *x = _root;
  while (x) x = x->_right;
  return iterator(_root, x);
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::find(
    const_reference key) {
  iterator result = end();
  Node *x = _root;
  while (x != nullptr) {
    if (key == x->_value) {
      result = iterator(_root, x);
      break;
    } else if (key < x->_value) {
      x = x->_left;
    } else {
      x = x->_right;
    }
  }
  return result;
}

template <class value_type>
bool s21::multiset<value_type>::contains(const_reference key) {
  return Contains(key);
}

template <class value_type>
bool s21::multiset<value_type>::empty() {
  return (_root == nullptr && size_ == 0);
}

template <class value_type>
std::size_t s21::multiset<value_type>::size() {
  return size_;
}

template <class value_type>
void s21::multiset<value_type>::erase(s21::multiset<value_type>::iterator pos) {
  if (contains(pos.ptr_->_key)) {
    Remove(pos.ptr_->_key);
    --size_;
  }
}

template <class value_type>
void s21::multiset<value_type>::clear() {
  s21::RBTree<value_type, value_type>::Destory(_root);
  size_ = 0;
  _root = nullptr;
}

template <class value_type>
void s21::multiset<value_type>::swap(s21::multiset<value_type> &other) {
  std::swap(_root, other._root);
  std::swap(size_, other.size_);
}

template <class value_type>
std::size_t s21::multiset<value_type>::count(const_reference key) {
  size_type count = 0;
  if (contains(key)) {
    iterator it = begin();
    iterator it_end = end();
    while (it != it_end) {
      if (*it == key) {
        ++count;
      } else if (*it > key) {
        break;
      }
      ++it;
    }
  }
  return count;
}

template <class value_type>
void s21::multiset<value_type>::merge(s21::multiset<value_type> &other) {
  for (auto n : other) {
    insert(n);
  }
  other.clear();
}

template <class value_type>
typename s21::multiset<value_type>::iterator
s21::multiset<value_type>::lower_bound(const_reference key) {
  iterator it = begin();
  iterator it_end = end();
  while (it != it_end && *it < key) {
    ++it;
  }
  return it;
}

template <class value_type>
typename s21::multiset<value_type>::iterator
s21::multiset<value_type>::upper_bound(const_reference key) {
  iterator it = begin();
  iterator it_end = end();
  while (it != it_end && *it <= key) {
    ++it;
  }
  return it;
}

template <class value_type>
std::pair<typename s21::multiset<value_type>::iterator,
          typename s21::multiset<value_type>::iterator>
s21::multiset<value_type>::equal_range(const_reference key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <class value_type>
std::size_t s21::multiset<value_type>::max_size() {
  return SIZE_MAX / ((sizeof(size_t) * 5) * 2);
}

template <class value_type>
template <class... Args>
s21::vector<std::pair<typename s21::multiset<value_type>::iterator, bool>>
s21::multiset<value_type>::emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result;
  std::pair<iterator, bool> elm;
  std::initializer_list<key_type> arg{args...};
  for (auto &val : arg) {
    elm.first = insert(val);
    elm.second = true;
    result.push_back(elm);
  }
  return result;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_MULTISET__H_
