#ifndef CPP2_S21_CONTAINERS_SRC_S21_NOD_SINGLE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_NOD_SINGLE_H_

namespace s21 {
template <typename T>
class node_single {
 public:
  T value_;
  node_single *next_;

  node_single() : value_(0), next_(nullptr) {}
  explicit node_single(T val) : value_(val), next_(nullptr) {}
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_NOD_SINGLE_H_
