#ifndef CPP2_S21_CONTAINERS_SRC_S21_NODE_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_NODE_TREE_H_

namespace s21 {
enum Color {
  RED,
  BLACK,
};

template <class K, class V>
struct RBTreeNode {
  K _key;
  V _value;
  RBTreeNode<K, V> *_left;
  RBTreeNode<K, V> *_right;
  RBTreeNode<K, V> *_parent;

  Color _color;  //цвет

  RBTreeNode(const K &key, const V &value)
      : _key(key),
        _value(value),
        _left(NULL),
        _right(NULL),
        _parent(NULL),
        _color(RED)  // Цвет узла по умолчанию красный
  {}
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_NODE_TREE_H_