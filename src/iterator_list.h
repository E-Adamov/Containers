#ifndef CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_LIST_H_

#include "node_double.h"

namespace s21 {
template <typename T>
class ListIterator {
 public:
  ListIterator() : ptr_node_(nullptr) {}
  explicit ListIterator(node_double<T> *pn) : ptr_node_(pn) {}

  T &operator*();
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator==(const ListIterator &other) const;
  bool operator!=(const ListIterator &other) const;

  node_double<T> *ptr_node_;
};

template <typename T>
T &s21::ListIterator<T>::operator*() {
  return ptr_node_->value_;
}

template <typename T>
bool s21::ListIterator<T>::operator==(const s21::ListIterator<T> &other) const {
  return (ptr_node_ == other.ptr_node_);
}

template <typename T>
bool s21::ListIterator<T>::operator!=(const s21::ListIterator<T> &other) const {
  return (ptr_node_ != other.ptr_node_);
}

template <typename T>
typename s21::ListIterator<T> &s21::ListIterator<T>::operator++() {
  ptr_node_ = ptr_node_->next_;
  return *this;
}

template <typename T>
typename s21::ListIterator<T> s21::ListIterator<T>::operator++(int) {
  ListIterator ret = *this;
  ++*(this);
  return ret;
}

template <typename T>
typename s21::ListIterator<T> &s21::ListIterator<T>::operator--() {
  ptr_node_ = ptr_node_->prev_;
  return *this;
}

template <typename T>
typename s21::ListIterator<T> s21::ListIterator<T>::operator--(int) {
  ListIterator ret = *this;
  --*(this);
  return ret;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_ITERATOR_LIST_H_