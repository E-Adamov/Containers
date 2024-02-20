#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <cstddef>           // для std::size_t
#include <initializer_list>  // для std::initializer_list

namespace s21 {
template <typename T, std::size_t n>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  array();
  explicit array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type size_{0U};
  value_type *data_{nullptr};

  void remove();
  void copy(const array &a);
  void move(array &a);
};

template <typename value_type, std::size_t n>
array<value_type, n>::array() : size_(n) {
  if (n != 0) data_ = new value_type[n];
}

template <typename value_type, std::size_t n>
array<value_type, n>::array(std::initializer_list<value_type> const &items)
    : array() {
  if (items.size() > n) {
    throw std::invalid_argument("error: too many initializers");
  }

  int i{0};
  for (auto item : items) {
    data_[i] = item;
    ++i;
  }
}

template <typename value_type, std::size_t n>
array<value_type, n>::array(const array &a) : array() {
  copy(a);
}

template <typename value_type, std::size_t n>
array<value_type, n>::array(array &&a) {
  move(a);
}

template <typename value_type, std::size_t n>
array<value_type, n>::~array() {
  remove();
}

template <typename value_type, std::size_t n>
array<value_type, n> array<value_type, n>::operator=(array &&a) {
  if (a != this) {
    move(a);
  }
  return *this;
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::iterator array<value_type, n>::begin() {
  return &data_[0];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::iterator array<value_type, n>::end() {
  return &data_[n];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::reference array<value_type, n>::at(
    size_type pos) {
  if (!(pos < n)) throw std::out_of_range("Out of range");
  return data_[pos];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::reference array<value_type, n>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::const_reference array<value_type, n>::front() {
  return data_[0];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::const_reference array<value_type, n>::back() {
  return data_[n - 1];
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::iterator array<value_type, n>::data() {
  return data_;
}

template <typename value_type, std::size_t n>
bool array<value_type, n>::empty() {
  return begin() == end();
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::size_type array<value_type, n>::size() {
  return n;
}

template <typename value_type, std::size_t n>
typename array<value_type, n>::size_type array<value_type, n>::max_size() {
  return n;
}

template <typename value_type, std::size_t n>
void array<value_type, n>::swap(array &other) {
  if (this != &other) {
    std::swap(other.size_, size_);
    std::swap(other.data_, data_);
  }
}

template <typename value_type, std::size_t n>
void array<value_type, n>::fill(const_reference value) {
  for (size_type i = 0; i < n; ++i) {
    data_[i] = value;
  }
}

template <typename value_type, std::size_t n>
void array<value_type, n>::remove() {
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0U;
  }
}

template <typename value_type, std::size_t n>
void array<value_type, n>::copy(const array &a) {
  if (this != &a) {
    std::copy(a.data_, a.data_ + n, data_);
  }
}

template <typename value_type, std::size_t n>
void array<value_type, n>::move(array &a) {
  remove();
  std::swap(size_, a.size_);
  std::swap(data_, a.data_);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
