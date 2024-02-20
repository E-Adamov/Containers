#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

#include <cstddef>           // для std::size_t
#include <initializer_list>  // для istd::nitializer_list
#include <stdexcept>         // для исключений

#include "iterator_list.h"
#include "node_double.h"

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = const ListIterator<T>;
  using size_type = std::size_t;

  typedef s21::node_double<value_type> Node;

  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list operator=(list &&l);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  size_type size_;
  Node *head_;
  Node *tail_;

  void creat_first_node(const_reference value);
};

template <typename T>
s21::list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
s21::list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_front(0);
  }
}

template <typename T>
s21::list<T>::list(const std::initializer_list<T> &items) : list() {
  for (auto item : items) {
    push_back(item);
  }
}

template <typename T>
s21::list<T>::list(const s21::list<T> &l) : list() {
  for (Node *i = l.head_; i != l.tail_->next_;) {
    push_back(i->value_);
    i = i->next_;
  }
}

template <typename T>
s21::list<T>::list(s21::list<T> &&l) : list() {
  swap(l);
}

template <typename T>
s21::list<T> s21::list<T>::operator=(s21::list<T> &&l) {
  clear();
  swap(l);
}

template <typename T>
s21::list<T>::~list() {
  clear();
}

template <typename T>
void s21::list<T>::creat_first_node(const_reference value) {
  Node *new_node = new node_double(value);
  ++size_;
  head_ = tail_ = new_node;
  head_->next_ = nullptr;
  head_->prev_ = nullptr;
}

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  if (size_ == 0) {
    creat_first_node(value);
  } else {
    Node *new_node = new node_double(value);
    ++size_;
    head_->prev_ = new_node;
    new_node->next_ = head_;
    new_node->prev_ = nullptr;
    head_ = new_node;
  }
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  if (size_ == 0) {
    creat_first_node(value);
  } else {
    Node *new_node = new node_double(value);
    ++size_;
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    new_node->next_ = nullptr;
    tail_ = new_node;
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  return iterator(tail_->next_);
}

template <typename T>
void s21::list<T>::swap(s21::list<T> &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <typename T>
void s21::list<T>::erase(s21::list<T>::iterator pos) {
  if (empty()) throw std::invalid_argument("the list is empty");
  pos.ptr_node_ == head_ ? head_ = head_->next_
                         : (pos.ptr_node_->prev_)->next_ = pos.ptr_node_->next_;
  pos.ptr_node_ == tail_ ? tail_ = tail_->prev_
                         : (pos.ptr_node_->next_)->prev_ = pos.ptr_node_->prev_;
  delete pos.ptr_node_;
  --size_;
}

template <typename T>
void s21::list<T>::pop_front() {
  if (empty()) throw std::invalid_argument("the list is empty");
  erase(iterator(head_));
}

template <typename T>
void s21::list<T>::pop_back() {
  if (empty()) throw std::invalid_argument("the list is empty");
  erase(iterator(tail_));
}

template <typename T>
void s21::list<T>::clear() {
  while (size_) pop_back();
}

template <typename T>
const T &s21::list<T>::front() {
  if (empty()) throw std::invalid_argument("the list is empty");
  return head_->value_;
}

template <typename T>
const T &s21::list<T>::back() {
  if (empty()) throw std::invalid_argument("the list is empty");
  return tail_->value_;
}

template <typename T>
bool s21::list<T>::empty() {
  return (head_ == nullptr && size_ == 0);
}

template <typename T>
std::size_t s21::list<T>::size() {
  return size_;
}

template <typename T>
std::size_t s21::list<T>::max_size() {
  return SIZE_MAX / (sizeof(Node) * 2);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(s21::list<T>::iterator pos,
                                                     const_reference value) {
  iterator result;
  if (size_ == 0) {
    creat_first_node(value);
    result = iterator(head_);
  } else if (pos.ptr_node_ == head_) {
    push_front(value);
    result = iterator(head_);
  } else if (pos.ptr_node_ == tail_->next_) {
    push_back(value);
    result = iterator(tail_);
  } else {
    Node *elm1 = pos.ptr_node_;
    Node *elm2 = new node_double(value);
    ++size_;

    elm2->next_ = elm1;
    elm2->prev_ = elm1->prev_;
    elm1->prev_->next_ = elm2;
    elm1->prev_ = elm2;

    result = iterator(elm2);
  }
  return result;
}

template <typename T>
void s21::list<T>::splice(s21::list<T>::iterator pos, s21::list<T> &other) {
  Node *elm1 = pos.ptr_node_;
  Node *elm2 = other.head_;
  Node *elm3 = other.tail_;

  elm3->next_ = elm1;
  if (elm1 != head_) {
    elm2->prev_ = elm1->prev_;
    elm1->prev_->next_ = elm2;
  }
  elm1->prev_ = elm3;
  if (elm1 == head_) head_ = other.head_;

  size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void s21::list<T>::sort() {
  for (size_type j = 0; j < size_; ++j) {
    for (Node *i = head_; i != tail_; i = i->next_) {
      Node *elm1 = i;
      Node *elm2 = elm1->next_;
      if (elm1->value_ > elm2->value_) {
        std::swap(elm1->value_, elm2->value_);
      }
    }
  }
}

template <typename T>
void s21::list<T>::reverse() {
  tail_ = head_;
  Node *elm = tail_->next_;
  while (tail_->next_) {
    head_->prev_ = elm;
    tail_->next_ = elm->next_;
    elm->next_ = head_;
    elm->prev_ = nullptr;
    head_ = elm;
    elm = tail_->next_;
  }
  tail_->next_ = nullptr;
}

template <typename T>
void s21::list<T>::unique() {
  iterator it = begin();
  while (it.ptr_node_ != tail_) {
    iterator it_next = it;
    ++it_next;
    if (*it == *it_next) erase(it_next);
    ++it;
  }
}

template <typename T>
void s21::list<T>::merge(s21::list<T> &other) {
  Node *elm1 = head_;
  Node *elm2 = other.head_;

  while (other.head_ && elm1 != tail_->next_) {
    if (elm2->value_ < elm1->value_) {
      other.head_ = elm2->next_;
      elm2->next_ = elm1;
      if (elm1 != head_) {
        elm2->prev_ = elm1->prev_;
        elm1->prev_->next_ = elm2;
      }
      elm1->prev_ = elm2;
      if (elm1 == head_) head_ = elm2;
      elm2 = other.head_;
      ++size_;
      --other.size_;
    } else {
      elm1 = elm1->next_;
    }
  }
  while (other.size_) {
    other.head_ = elm2->next_;
    elm2->next_ = tail_->next_;
    elm2->prev_ = tail_;
    tail_->next_ = elm2;
    tail_ = elm2;
    elm2 = other.head_;
    ++size_;
    --other.size_;
  }
}

template <class T>
template <class... Args>
void list<T>::emplace_front(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push_front(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push_front(val);
}

template <class T>
template <class... Args>
void list<T>::emplace_back(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push_back(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push_back(val);
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    insert(pos, _empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) insert(pos, val);
  return pos;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
