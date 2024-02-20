#ifndef CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_

#include <initializer_list>  // для std::initializer_list

#include "node_single.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  typedef s21::node_single<value_type> Node;

  queue();
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue operator=(queue &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  size_type size_;
  Node *head_;
  Node *tail_;

  void creat_first_node(const_reference value);
  void remove();
};

template <typename value_type>
s21::queue<value_type>::queue() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename value_type>
s21::queue<value_type>::queue(const std::initializer_list<value_type> &items)
    : queue() {
  for (auto item : items) {
    push(item);
  }
}

template <typename value_type>
s21::queue<value_type>::queue(const s21::queue<value_type> &q) : queue() {
  if (q.head_) {
    for (Node *i = q.head_; i != q.tail_->next_;) {
      push(i->value_);
      i = i->next_;
    }
  }
}

template <typename value_type>
s21::queue<value_type>::queue(s21::queue<value_type> &&q) : queue() {
  swap(q);
}

template <typename value_type>
s21::queue<value_type>::~queue() {
  remove();
}

template <typename value_type>
bool s21::queue<value_type>::empty() {
  return (head_ == nullptr && size_ == 0);
}

template <typename value_type>
void s21::queue<value_type>::remove() {
  while (size_) pop();
}

template <typename value_type>
s21::queue<value_type> s21::queue<value_type>::operator=(
    s21::queue<value_type> &&q) {
  remove();
  swap(q);
}

template <typename value_type>
void s21::queue<value_type>::creat_first_node(const_reference value) {
  Node *new_node = new Node(value);
  ++size_;
  head_ = tail_ = new_node;
  head_->next_ = nullptr;
}

template <typename value_type>
void s21::queue<value_type>::push(const_reference value) {
  if (size_ == 0) {
    creat_first_node(value);
  } else {
    Node *new_node = new Node(value);
    ++size_;
    tail_->next_ = new_node;
    new_node->next_ = nullptr;
    tail_ = new_node;
  }
}

template <typename value_type>
void s21::queue<value_type>::pop() {
  if (empty()) throw std::invalid_argument("the queue is empty");
  Node *node_to_delete = head_;
  head_ = head_->next_;
  delete node_to_delete;
  --size_;
}

template <typename value_type>
void s21::queue<value_type>::swap(s21::queue<value_type> &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <typename value_type>
const value_type &s21::queue<value_type>::front() {
  if (empty()) throw std::invalid_argument("the queue is empty");
  return head_->value_;
}

template <typename value_type>
const value_type &s21::queue<value_type>::back() {
  if (empty()) throw std::invalid_argument("the queue is empty");
  return tail_->value_;
}

template <typename value_type>
std::size_t s21::queue<value_type>::size() {
  return size_;
}

template <class value_type>
template <class... Args>
void queue<value_type>::emplace_back(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty{};
    push(_empty);
  }
  std::initializer_list<value_type> arg{args...};
  for (auto &val : arg) push(val);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_