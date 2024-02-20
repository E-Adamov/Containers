#ifndef CPP2_S21_CONTAINERS_SRC_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_S21_MAP_H_

#include <cstddef>           // для std::size_t
#include <initializer_list>  // для std::initializer_list
#include <utility>           // для std::pair

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map : RBTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21::RBTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename s21::RBTree<key_type, mapped_type>::const_iterator;
  using size_type = std::size_t;

  typedef s21::RBTreeNode<key_type, mapped_type> Node;

  map(){};
  explicit map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map(){};
  map operator=(map &&m);

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const key_type &key);
  iterator find(const key_type &key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  size_type size_{0};
  using s21::RBTree<key_type, mapped_type>::_root;
  using s21::RBTree<key_type, mapped_type>::Contains;
  using s21::RBTree<key_type, mapped_type>::Insert;
  using s21::RBTree<key_type, mapped_type>::Remove;
};

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(
    const std::initializer_list<value_type> &items) {
  for (value_type item : items) {
    insert(item);
  }
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(const s21::map<key_type, mapped_type> &m) {
  iterator it = m.begin();
  iterator it_end = m.end();
  while (it != it_end) {
    insert(it.ptr_->_key, it.ptr_->_value);
    ++it;
  }
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(s21::map<key_type, mapped_type> &&m) {
  clear();
  swap(m);
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type> s21::map<key_type, mapped_type>::operator=(
    s21::map<key_type, mapped_type> &&m) {
  clear();
  swap(m);
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::clear() {
  s21::RBTree<key_type, mapped_type>::Destory(_root);
  size_ = 0;
  _root = nullptr;
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert(const_reference value) {
  std::pair<iterator, bool> result;
  if (!contains(value.first)) {
    Insert(value.first, value.second);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
  }
  result.first = find(value.first);
  return result;
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert(const key_type &key,
                                        const mapped_type &obj) {
  std::pair<iterator, bool> result;
  if (!contains(key)) {
    Insert(key, obj);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
  }
  result.first = find(key);
  return result;
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                                  const mapped_type &obj) {
  std::pair<iterator, bool> result;
  if (!contains(key)) {
    Insert(key, obj);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
    iterator it = find(key);
    it.ptr_->_value = obj;
  }
  result.first = find(key);
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::erase(
    s21::map<key_type, mapped_type>::iterator pos) {
  if (contains(pos.ptr_->_key)) {
    Remove(pos.ptr_->_key);
    --size_;
  }
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::iterator
s21::map<key_type, mapped_type>::begin() const {
  Node *x = _root;
  while (x->_left) x = x->_left;
  return iterator(_root, x);
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::iterator
s21::map<key_type, mapped_type>::end() const {
  Node *x = _root;
  while (x) x = x->_right;
  return iterator(_root, x);
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::iterator
s21::map<key_type, mapped_type>::find(const key_type &key) {
  iterator result = end();
  Node *x = _root;
  while (x != nullptr) {
    if (key == x->_key) {
      result = iterator(_root, x);
      break;
    } else if (key < x->_key) {
      x = x->_left;
    } else {
      x = x->_right;
    }
  }
  return result;
}

template <class key_type, class mapped_type>
mapped_type &s21::map<key_type, mapped_type>::at(const key_type &key) {
  if (!contains(key)) {
    throw std::out_of_range("Out of range");
  }
  iterator it = find(key);

  return it.ptr_->_value;
}

template <class key_type, class mapped_type>
mapped_type &s21::map<key_type, mapped_type>::operator[](const key_type &key) {
  if (!contains(key)) {
    insert(key, mapped_type());
  }
  iterator it = find(key);
  return it.ptr_->_value;
}

template <class key_type, class mapped_type>
bool s21::map<key_type, mapped_type>::contains(const key_type &key) {
  return Contains(key);
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::swap(
    s21::map<key_type, mapped_type> &other) {
  std::swap(_root, other._root);
  std::swap(size_, other.size_);
}

template <class key_type, class mapped_type>
bool s21::map<key_type, mapped_type>::empty() {
  return (_root == nullptr && size_ == 0);
}

template <class key_type, class mapped_type>
std::size_t s21::map<key_type, mapped_type>::size() {
  return size_;
}

template <class key_type, class mapped_type>
std::size_t s21::map<key_type, mapped_type>::max_size() {
  return SIZE_MAX / (sizeof(Node) * 2);
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::merge(
    s21::map<key_type, mapped_type> &other) {
  s21::map<key_type, mapped_type> temp(other);
  other.clear();
  iterator it = temp.begin();
  iterator it_end = temp.end();
  while (it != it_end) {
    if (!contains(it.ptr_->_key)) {
      insert(it.ptr_->_key, it.ptr_->_value);
    } else {
      other.insert(it.ptr_->_key, it.ptr_->_value);
    }
    ++it;
  }
  temp.clear();
}

template <class key_type, class mapped_type>
template <class... Args>
s21::vector<std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>>
s21::map<key_type, mapped_type>::emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result;
  std::pair<iterator, bool> elm;
  std::initializer_list<value_type> arg{args...};
  for (value_type val : arg) {
    elm = insert(val);
    result.push_back(elm);
  }
  return result;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_MAP_H_
