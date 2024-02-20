#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_H_

// https://www.cyberforum.ru/cpp-beginners/thread2765490.html

#include <initializer_list>  // для std::initializer_list

#include "node_single.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  typedef s21::node_single<value_type> Node;

  stack() {}
  explicit stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  reference operator=(stack &&s);

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void emplace_front(Args &&...args);

 private:
  size_type size_{0U};
  Node *head_{nullptr};

  void copy(Node *n);
  void move(stack *s);
  void remove();
};

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items) {
  for (auto item : items) push(item);
}

template <typename value_type>
stack<value_type>::stack(const stack &s) : size_(0), head_(nullptr) {
  if (this != &s) copy(s.head_);
}

template <typename value_type>
stack<value_type>::stack(stack &&s) {
  move(&s);
}

template <typename value_type>
stack<value_type>::~stack() {
  remove();
}

template <typename value_type>
typename stack<value_type>::reference stack<value_type>::operator=(stack &&s) {
  move(s);
  return *this;
}

template <typename value_type>
typename stack<value_type>::const_reference stack<value_type>::top() const {
  return head_->value_;
}

template <typename value_type>
bool stack<value_type>::empty() const {
  bool result = false;
  if (size_ == 0 || head_ == nullptr) result = true;

  return result;
}

template <typename value_type>
typename stack<value_type>::size_type stack<value_type>::size() const {
  return size_;
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  Node *new_node = new Node(value);
  new_node->next_ = head_;
  head_ = new_node;
  ++size_;
}

template <typename value_type>
void stack<value_type>::pop() {
  if (!empty()) {
    Node *temp = head_;
    head_ = head_->next_;
    delete temp;
    --size_;
  }
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  if (this != &other) {
    std::swap(other.size_, size_);
    std::swap(other.head_, head_);
  }
}

template <typename value_type>
void stack<value_type>::copy(Node *n) {
  if (!n) return;
  copy(n->next_);
  push(n->value_);
}

template <typename value_type>
void stack<value_type>::move(stack *s) {
  if (this != s) {
    remove();
    size_ = s->size_;
    head_ = s->head_;
    s->size_ = 0;
    s->head_ = nullptr;
  }
}

template <typename value_type>
void stack<value_type>::remove() {
  while (size_) pop();
}

template <class value_type>
template <class... Args>
void stack<value_type>::emplace_front(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push(_empty);
  }
  std::initializer_list<value_type> arg{args...};
  for (auto &val : arg) push(val);
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
