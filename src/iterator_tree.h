#ifndef CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_H_

#include "node_tree.h"

namespace s21 {
template <class Key, class Value>
class RBTreeIterator {
 public:
  using key_type = Key;
  using value_type = Value;

  typedef RBTreeNode<key_type, value_type> Node;
  RBTreeIterator() {}
  RBTreeIterator(Node *root, Node *ptr) : root_(root), ptr_(ptr) {}

  RBTreeIterator &operator=(const RBTreeIterator &other);
  RBTreeIterator operator++();
  RBTreeIterator operator--();
  value_type operator*();
  bool operator==(const RBTreeIterator &other) const;
  bool operator!=(const RBTreeIterator &other) const;

  Node *root_{nullptr};
  Node *ptr_{nullptr};
};

template <class key_type, class value_type>
s21::RBTreeIterator<key_type, value_type>
    &s21::RBTreeIterator<key_type, value_type>::operator=(
        const s21::RBTreeIterator<key_type, value_type> &other) {
  if (*this != other) {
    root_ = other.root_;
    ptr_ = other.ptr_;
  }

  return *this;
}

template <typename key_type, typename value_type>
RBTreeIterator<key_type, value_type>
RBTreeIterator<key_type, value_type>::operator++() {
  if (ptr_ == nullptr) {
    ptr_ = root_;

  } else if (ptr_->_right != nullptr) {
    ptr_ = ptr_->_right;

    while (ptr_->_left != nullptr) ptr_ = ptr_->_left;
  } else {
    Node *tmp = ptr_->_parent;

    while (tmp != nullptr && ptr_ == tmp->_right) {
      ptr_ = tmp;
      tmp = ptr_->_parent;
    }

    ptr_ = tmp;
  }

  return *this;
}

template <typename key_type, typename value_type>
RBTreeIterator<key_type, value_type>
RBTreeIterator<key_type, value_type>::operator--() {
  if (ptr_ == nullptr) {
    ptr_ = root_;
    Node *tmp = ptr_;

    while (tmp != nullptr) {
      ptr_ = tmp;
      tmp = tmp->_right;
    }
  } else if (ptr_->_left != nullptr) {
    ptr_ = ptr_->_left;

    while (ptr_->_right != nullptr) {
      ptr_ = ptr_->_right;
    }
  } else {
    Node *tmp = ptr_->_parent;

    while (tmp != nullptr && ptr_ == tmp->_left) {
      ptr_ = tmp;
      tmp = ptr_->_parent;
    }

    ptr_ = tmp;
  }

  return *this;
}

template <typename key_type, typename value_type>
value_type RBTreeIterator<key_type, value_type>::operator*() {
  return ptr_->_value;
}

template <typename key_type, typename value_type>
bool RBTreeIterator<key_type, value_type>::operator==(
    const RBTreeIterator &other) const {
  return ptr_ == other.ptr_;
}

template <typename key_type, typename value_type>
bool RBTreeIterator<key_type, value_type>::operator!=(
    const RBTreeIterator &other) const {
  return ptr_ != other.ptr_;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_H_
