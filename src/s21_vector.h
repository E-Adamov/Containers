#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <cstring>           // для std::memcpy
#include <initializer_list>  // для std::initializer_list

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = size_t;

  vector() {}
  explicit vector(size_type n);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  reference operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data() const;

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);  //
  void erase(iterator pos);
  void push_back(value_type value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  size_type size_{0U};
  size_type capacity_{0U};
  iterator data_{nullptr};

  void copy(const vector &v);
  void move(vector *v);
  void remove();
  void allocate(size_type size);
};

template <typename value_type>
vector<value_type>::vector(size_type n) : size_(n), capacity_(n) {
  if (n > max_size())
    throw std::length_error("Cannot create vector larger than max_size()");

  data_ = (n) ? new value_type[n] : nullptr;
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
  size_ = items.size();

  data_ = (size_) ? new value_type[size_] : nullptr;

  if (data_) {
    for (auto &i : items) {
      data_[capacity_] = i;
      capacity_ += 1;
    }
  }
}

template <typename value_type>
vector<value_type>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_) {
  copy(v);
}

template <typename value_type>
vector<value_type>::vector(vector &&v) {
  move(&v);
}

template <typename value_type>
vector<value_type>::~vector() {
  remove();
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator=(
    vector &&v) {
  move(v);
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Out of range");

  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    const size_type index) const {
  return data_[index];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return data_[size_ - 1];
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::data() const {
  return data_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return &data_[0];
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return &data_[size_];
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return (size_ == 0 || data_ == nullptr) ? true : false;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  return SIZE_MAX / (sizeof(value_type) * 2);
}

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > capacity_) allocate(size);
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return capacity_;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ < capacity_) allocate(size_);
}

template <typename value_type>
void vector<value_type>::clear() {
  while (size_) pop_back();
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type index = 0;
  if (empty()) {
    reserve(1);
    push_back(value);
  } else {
    value_type last = back();
    while (&data_[index] != pos) {
      ++index;
    }
    if (pos != end()) {
      for (iterator it = end() - 1; it != pos; --it) {
        *it = *(it - 1);
      }
      *pos = value;
      push_back(last);
    } else {
      push_back(value);
    }
  }
  return &data_[index];
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  if (size_ != 0) {
    for (; pos + 1 != end(); pos += 1) {
      *pos = *(pos + 1);
    }

    size_ -= 1;
  }
}

template <typename value_type>
void vector<value_type>::push_back(value_type value) {
  if (empty()) reserve(1);
  if (size_ == capacity_) allocate(capacity_ * 2);

  data_[size_++] = value;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (!empty()) {
    --size_;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector &other) {
  if (this != &other) {
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
    std::swap(other.data_, data_);
  }
}

template <typename value_type>
void vector<value_type>::copy(const vector &v) {
  if (this != &v) {
    data_ = (size_) ? new value_type[size_] : nullptr;

    if (data_) std::memcpy(data_, v.data_, v.size_ * sizeof(value_type));
  }
}

template <typename value_type>
void vector<value_type>::move(vector *v) {
  if (this != v) {
    remove();
    data_ = v->data_;
    capacity_ = v->capacity_;
    size_ = v->size_;
    v->data_ = nullptr;
    v->capacity_ = v->size_ = 0;
  }
}

template <typename value_type>
void vector<value_type>::remove() {
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = size_ = 0;
  }
}

template <typename value_type>
void vector<value_type>::allocate(size_type size) {
  if (size > max_size())
    throw std::length_error("Cannot create vector larger than max_size()");

  if (size == 0) {
    remove();
  } else {
    size_type size_temp = (size_ > size) ? size : size_;

    iterator data_temp = nullptr;

    if (data_ != nullptr) {
      data_temp = new value_type[size_temp];
      std::memcpy(data_temp, data_, size_temp * sizeof(value_type));
      delete[] data_;
    }

    data_ = new value_type[size];

    if (data_temp != nullptr) {
      std::memcpy(data_, data_temp, size_temp * sizeof(value_type));
      delete[] data_temp;
    }

    capacity_ = size;
  }
}

template <class value_type>
template <class... Args>
void vector<value_type>::emplace_back(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push_back(_empty);
  }
  std::initializer_list<value_type> arg{args...};
  for (auto &val : arg) {
    if (empty()) {
      reserve(1);
      push_back(val);
    } else {
      push_back(val);
    }
  }
}

template <class value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(
    const_iterator pos, Args &&...args) {
  iterator it = iterator(pos);
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    insert(it, _empty);
  }
  std::initializer_list<value_type> arg{args...};
  for (auto &val : arg) {
    it = insert(it, val);
    ++it;
  }
  return it;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_