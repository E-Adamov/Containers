#ifndef CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_

#include "iterator_tree.h"
#include "node_tree.h"

namespace s21 {

template <class K, class V>
class RBTree {
 public:
  using key_type = K;
  using value_type = V;
  typedef RBTreeNode<key_type, value_type> Node;
  using iterator = RBTreeIterator<key_type, value_type>;
  using const_iterator = const RBTreeIterator<key_type, value_type>;

  RBTree() : _root(NULL) {}
  explicit RBTree(const RBTree<key_type, value_type> &tree) {
    Copy(tree._root, _root);
  }
  RBTree operator=(RBTree &tree);
  ~RBTree() { Destory(_root); }

  void Insert(const key_type &key, const value_type &value);
  void Creat_new_node(Node *cur, Node *parent, const key_type &key,
                      const value_type &value);
  void Balance_insert(Node *cur, Node *parent);

  void Remove(const key_type &key);
  void Case_to_delete_one(Node *cur, Node *parent, Node *del);
  void Case_to_delete_two(Node *cur, Node *parent, Node *del);
  void Case_to_delete_three(Node *cur, Node *parent, Node *del);
  void Case_to_delete_four(Node *cur, Node *parent, Node *del);

  bool Contains(const key_type &key);

 protected:
  void Copy(Node *root, Node *new_root);
  void Destory(Node *root);
  void RotateR(Node *parent);
  void RotateL(Node *parent);
  Node *_root;
};

template <class key_type, class value_type>
s21::RBTree<key_type, value_type> s21::RBTree<key_type, value_type>::operator=(
    s21::RBTree<key_type, value_type> &tree) {
  if (this != &tree) {
    RBTree<key_type, value_type> tmp(tree);
    std::swap(_root, tmp._root);
  }
  return *this;
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Remove(const key_type &key) {
  Node *cur = _root;
  Node *parent = NULL;
  Node *del = NULL;

  while (cur) {  // Найти узел, который нужно удалить
    if (cur->_key > key) {
      cur = cur->_left;
    } else if (cur->_key < key) {
      cur = cur->_right;
    } else {
      break;
    }
  }
  del = cur;

  // Если удаляемый узел имеет двух потомков, вам нужно найти самый левый узел
  // правого поддерева
  if (cur && cur->_left != NULL && cur->_right != NULL) {
    cur = cur->_right;
    while (cur->_left) {
      cur = cur->_left;
    }
    del->_key = cur->_key;
    del->_value = cur->_value;
    del = cur;
  }
  if (cur) parent = cur->_parent;  // найти отца удаляемого узла

  Case_to_delete_one(cur, parent, del);
  if (_root) _root->_color = BLACK;
  delete del;
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Case_to_delete_one(Node *cur,
                                                           Node *parent,
                                                           Node *del) {
  if (cur->_left == NULL) {  // Левый потомок удаляемого узла пуст или оба пусты
    if (parent == NULL) {
      _root = cur->_right;
      if (cur->_right) {
        _root->_parent = NULL;
        _root->_color = BLACK;
      }
    } else {
      if (parent->_left == cur) {
        parent->_left = cur->_right;
      } else {
        parent->_right = cur->_right;
      }
      if (cur->_right) {
        cur->_right->_parent = parent;
      }

      cur = del->_right;
      Case_to_delete_two(cur, parent, del);
    }
  } else {  // Правый потомок удаляемого узла пуст
    if (parent == NULL) {
      _root = cur->_left;
      _root->_parent = NULL;
      _root->_color = BLACK;
    } else {
      if (parent->_left == cur) {
        parent->_left = cur->_left;
      } else {
        parent->_right = cur->_left;
      }
      cur->_left->_parent = parent;
    }
    cur = del->_left;
    Case_to_delete_two(cur, parent, del);
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Case_to_delete_two(Node *cur,
                                                           Node *parent,
                                                           Node *del) {
  if (del->_color != RED) {  // если узел красный, удаляем
    Case_to_delete_three(cur, parent, del);
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Case_to_delete_three(Node *cur,
                                                             Node *parent,
                                                             Node *del) {
  if (del->_color == BLACK && cur && cur->_color == RED) {
    cur->_color = BLACK;
  } else {
    Case_to_delete_four(cur, parent, del);
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Case_to_delete_four(Node *cur,
                                                            Node *parent,
                                                            Node *del) {
  while (parent) {  // удаляемый узел черный, а его потомки NULL или черные
    if (parent->_left == cur) {
      Node *subR = parent->_right;
      if (subR->_color == RED) {
        RotateL(parent);
        subR->_color = BLACK;
        parent->_color = RED;
      } else {
        Node *subRL = subR->_left;
        Node *subRR = subR->_right;
        if (parent->_color == BLACK && (subRL == NULL && subRR == NULL) ||
            (subRL && subRL->_color == BLACK && subRR &&
             subRR->_color == BLACK)) {
          subR->_color = RED;
          cur = parent;
          parent = cur->_parent;
        } else {
          if (parent->_color == RED) {
            if ((subRL == NULL && subRR == NULL) ||
                (subRL && subRL->_color == BLACK && subRR &&
                 subRR->_color == BLACK)) {
              parent->_color = BLACK;
              subR->_color = RED;
              break;
            }
          }
          if (subRL && subRL->_color == RED) {
            RotateR(subR);
            subR = subRL;
          }
          RotateL(parent);
          if (parent->_color == RED) {
            subR->_color = RED;
          } else {
            subR->_color = BLACK;
          }
          parent->_color = BLACK;
          subR->_right->_color = BLACK;
          break;
        }
      }
    } else {
      Node *subL = parent->_left;
      if (subL->_color == RED) {
        RotateR(parent);
        parent->_color = RED;
        subL->_color = BLACK;
      } else {
        Node *subLR = subL->_right;
        Node *subLL = subL->_left;
        if (parent->_color == BLACK && (subLL == NULL && subLR == NULL) ||
            (subLL && subLL->_color == BLACK && subLR &&
             subLR->_color == BLACK)) {
          subL->_color = RED;
          cur = parent;
          parent = cur->_parent;
        } else {
          if (parent->_color == RED) {
            if ((subLL == NULL && subLR == NULL) ||
                (subLL && subLL->_color == BLACK && subLR &&
                 subLR->_color == BLACK)) {
              parent->_color = BLACK;
              subL->_color = RED;
              break;
            }
          }
          if (subLR && subLR->_color == RED) {
            RotateL(subL);
            subL = subLR;
          }
          RotateR(parent);
          if (parent->_color == RED) {
            subL->_color = RED;
          } else {
            subL->_color = BLACK;
          }
          parent->_color = BLACK;
          subL->_left->_color = BLACK;
          break;
        }
      }
    }
  }
}

template <class key_type, class value_type>
bool s21::RBTree<key_type, value_type>::Contains(const key_type &key) {
  bool result = false;
  Node *cur = _root;
  while (cur) {
    if (cur->_key < key) {
      cur = cur->_right;
    } else if (cur->_key > key) {
      cur = cur->_left;
    } else {
      result = true;
      break;
    }
  }
  return result;
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Insert(const key_type &key,
                                               const value_type &value) {
  if (_root == NULL) {  // Вставляем при пустом дереве
    _root = new Node(key, value);
    _root->_color = BLACK;
  } else {
    Node *parent{0};
    Node *cur = _root;
    Creat_new_node(cur, parent, key, value);
    _root->_color = BLACK;
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Creat_new_node(
    Node *cur, Node *parent, const key_type &key, const value_type &value) {
  while (cur) {  // найти позицию вставки
    if (cur->_key <= key) {
      parent = cur;
      cur = cur->_right;
    } else {
      parent = cur;
      cur = cur->_left;
    }
  }
  cur = new Node(key, value);
  cur->_color = RED;
  if (parent->_key <= key) {
    parent->_right = cur;
    cur->_parent = parent;
  } else {
    parent->_left = cur;
    cur->_parent = parent;
  }
  Balance_insert(cur, parent);
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Balance_insert(Node *cur,
                                                       Node *parent) {
  while (parent && parent->_color == RED) {
    Node *grand = parent->_parent;  // дедушка узел
    if (parent == grand->_left) {
      Node *uncle = grand->_right;  // дядя узел
      // Узел дядя существует и красный
      if (uncle && uncle->_color == RED) {
        parent->_color = BLACK;
        uncle->_color = BLACK;
        grand->_color = RED;
        cur = grand;
        parent = cur->_parent;
      } else {  // Узел дядя не существует, существует и является черным
        if (cur == parent->_right) {
          RotateL(parent);
          std::swap(cur, parent);
        }
        RotateR(grand);
        parent->_color = BLACK;
        grand->_color = RED;
      }
    } else {
      Node *uncle = grand->_left;
      // Узел дядя существует и красный
      if (uncle && uncle->_color == RED) {
        parent->_color = BLACK;
        uncle->_color = BLACK;
        grand->_color = RED;
        cur = grand;
        parent = cur->_parent;
      } else {  // Узел дядя не существует, существует и является черным
        if (cur == parent->_left) {
          RotateR(parent);
          std::swap(cur, parent);
        }
        RotateL(grand);
        parent->_color = BLACK;
        grand->_color = RED;
      }
    }
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Copy(Node *root, Node *new_root) {
  if (root != NULL) {
    Node *cur = new Node(root->_key, root->_value);
    cur->_color = root->_color;
    new_root = cur;
    cur->_parent = new_root;

    Copy(root->_left, cur->_left);
    Copy(root->_right, cur->_right);
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::Destory(Node *root) {
  if (root != NULL) {
    Destory(root->_left);
    Destory(root->_right);
    delete root;
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::RotateR(Node *parent) {
  Node *subL = parent->_left;
  Node *subLR = subL->_right;
  Node *ppNode = parent->_parent;

  parent->_left = subLR;

  if (subLR) {
    subLR->_parent = parent;
  }

  subL->_right = parent;
  parent->_parent = subL;

  if (ppNode == NULL) {
    _root = subL;
    subL->_parent = NULL;
  } else {
    if (ppNode->_left == parent) {
      ppNode->_left = subL;
    } else {
      ppNode->_right = subL;
    }

    subL->_parent = ppNode;
  }
}

template <class key_type, class value_type>
void s21::RBTree<key_type, value_type>::RotateL(Node *parent) {
  Node *subR = parent->_right;
  Node *subRL = subR->_left;
  Node *ppNode = parent->_parent;

  parent->_right = subRL;

  if (subRL) {
    subRL->_parent = parent;
  }

  subR->_left = parent;
  parent->_parent = subR;

  if (ppNode == NULL) {
    _root = subR;
    subR->_parent = NULL;
  } else {
    if (ppNode->_left == parent) {
      ppNode->_left = subR;
    } else {
      ppNode->_right = subR;
    }

    subR->_parent = ppNode;
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_
