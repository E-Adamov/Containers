#ifndef CPP2_S21_CONTAINERS_SRC_S21_NOD_DOUBLE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_NOD_DOUBLE_H_

namespace s21 {
template <typename T>
class node_double {
 public:
  T value_;
  node_double *next_;
  node_double *prev_;

  node_double() : value_(0), next_(nullptr), prev_(nullptr) {}
  explicit node_double(T val) : value_(val), next_(nullptr), prev_(nullptr) {}
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_NOD_DOUBLE_H_