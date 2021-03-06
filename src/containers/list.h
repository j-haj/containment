#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <memory>

template <class T, class Allocator> Node;
#ifdef DEBUG
  template <typename T>
  std::ostream& operator<<(std::ostream& os, Node<T>& o) {
    os << "Node< " << o.value << ", " << o.next.get() << ">";
    return os;
  }
#endif


template <class T, class Allocator>
class Node {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;

  typedef value_type& reference;
  typedef const value_type& const_reference;

  using NodePtr = std::unique_ptr<Node<T>>;
  Node(T val) : value(val), next(nullptr) {}
  // Note: on copies we only want to copy the value, not the pointer to the next
  // node
  Node(const Node& n) : value(n.value), next(nullptr) {}
  Node(Node&& n) : value(n.value) { next = NodePtr(n.next.release()); }
  ~Node() { next.reset(); }

  Node& operator=(Node& n) { return n; }

  /// Holds the data for the node
  T value;

  /// Unique pointer to next node in list
  NodePtr next;
};

template <typename T>
class ForwardList {
  using NodePtr = std::unique_ptr<Node<T>>;

 public:
  void insert(T v) {
    auto tmp = std::make_unique<Node<T>>(v);
    tmp->next.reset(head_.release());
    head_.reset(tmp.release());
  }

  size_t size() const noexcept { return size_; }

  Node<T>* head() { return head_.get(); }

 private:
  /// Number of nodes in the list
  size_t size_;

  /// Unique pointer to the head of the list
  NodePtr head_;

};  // class ForwardList

template <typename T>
std::ostream& operator<<(std::ostream& os, ForwardList<T>& o) {
  Node<T>* p = o.head();
  while (p->next != nullptr) {
    os << p->value << ' ';
  }
}

#endif  // LIST_H_
