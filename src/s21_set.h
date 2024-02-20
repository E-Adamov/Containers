#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET__H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET__H_

#include <cstddef>           // для std::size_t
#include <initializer_list>  // для std::initializer_list
#include <utility>           // для std::pair

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set : RBTree<Key, Key> {
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

  set(){};
  explicit set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set(){};
  set operator=(set &&s);

  iterator begin() const;
  iterator end() const;
  iterator find(const value_type &key);
  bool contains(const value_type &key);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

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
s21::set<value_type>::set(const std::initializer_list<value_type> &items) {
  for (auto item : items) {
    insert(item);
  }
}

template <class value_type>
s21::set<value_type>::set(const s21::set<value_type> &s) {
  iterator it_begin = s.begin();
  iterator it_end = s.end();
  while (it_begin != it_end) {
    insert(*it_begin);
    ++it_begin;
  }
}

template <class value_type>
s21::set<value_type>::set(s21::set<value_type> &&s) {
  clear();
  swap(s);
}

template <class value_type>
s21::set<value_type> s21::set<value_type>::operator=(s21::set<value_type> &&s) {
  clear();
  swap(s);
}

template <class value_type>
void s21::set<value_type>::clear() {
  s21::RBTree<value_type, value_type>::Destory(_root);
  size_ = 0;
  _root = nullptr;
}

template <class value_type>
std::pair<typename s21::set<value_type>::iterator, bool>
s21::set<value_type>::insert(const value_type &value) {
  std::pair<iterator, bool> result;
  if (!contains(value)) {
    Insert(value, value);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
  }
  result.first = find(value);
  return result;
}

template <class value_type>
void s21::set<value_type>::erase(s21::set<value_type>::iterator pos) {
  if (contains(pos.ptr_->_key)) {
    Remove(pos.ptr_->_key);
    --size_;
  }
}

template <class value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::begin() const {
  Node *x = _root;
  while (x->_left) x = x->_left;
  return iterator(_root, x);
}

template <class value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::end() const {
  Node *x = _root;
  while (x) x = x->_right;
  return iterator(_root, x);
}

template <class value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::find(
    const value_type &key) {
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
bool s21::set<value_type>::contains(const value_type &key) {
  return Contains(key);
}

template <class value_type>
void s21::set<value_type>::swap(s21::set<value_type> &other) {
  std::swap(_root, other._root);
  std::swap(size_, other.size_);
}

template <class value_type>
bool s21::set<value_type>::empty() {
  return (_root == nullptr && size_ == 0);
}

template <class value_type>
std::size_t s21::set<value_type>::size() {
  return size_;
}

template <class value_type>
std::size_t s21::set<value_type>::max_size() {
  return SIZE_MAX / ((sizeof(size_t) * 5) * 2);
}

template <class value_type>
void s21::set<value_type>::merge(s21::set<value_type> &other) {
  s21::set<value_type> temp(other);
  other.clear();
  for (auto n : temp) {
    if (!contains(n)) {
      insert(n);
    } else {
      other.insert(n);
    }
  }
  temp.clear();
}

template <class value_type>
template <class... Args>
s21::vector<std::pair<typename s21::set<value_type>::iterator, bool>>
s21::set<value_type>::emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result;
  std::pair<iterator, bool> elm;
  std::initializer_list<value_type> arg{args...};
  for (auto &val : arg) {
    elm = insert(val);
    result.push_back(elm);
  }
  return result;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET__H_
