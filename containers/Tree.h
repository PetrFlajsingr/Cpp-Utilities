//
// Created by petr on 12/21/19.
//

#ifndef UTILITIES_TREE_H
#define UTILITIES_TREE_H

#include <utility>

enum class NodeType {
  Leaf, Node
};

template <typename T, unsigned int ChildCount>
class Leaf {
public:
  using value_type = T;
  using pointer_type = T*;
  using const_pointer_type = const T*;
  using reference_type = T&;
  using const_reference_type = const T&;

  Leaf() = default;
  explicit Leaf(value_type value) : value(std::move(value)) {}
  Leaf(const Leaf &other) : value(other.value) {}
  Leaf &operator=(const Leaf &other) {
    if (&other == this) {
      return *this;
    }
    value = other.value;
    return *this;
  }
  Leaf(Leaf &&other) noexcept : value(std::move(other.value)) {}
  Leaf &operator=(Leaf &&other) noexcept {
    value = std::move(other.value);
    return *this;
  }

  const_reference_type operator*() {
    return value;
  }

  const_pointer_type operator->() {
    return value;
  }

  const_reference_type getValue() const { return value; }
  void setValue(value_type value) { Leaf::value = value; }

  [[nodiscard]] virtual NodeType getType() const {
    return NodeType::Leaf;
  }

  virtual ~Leaf() = default;

private:
  value_type value;
};

template <typename T, unsigned int ChildCount>
class Node : public Leaf<T, ChildCount> {
  using Base = Leaf<T, ChildCount>;
  using Child = Leaf<T, ChildCount>;
  using ChildPtr = std::unique_ptr<Leaf<T, ChildCount>>;
  using Children = std::array<ChildPtr, ChildCount>;
public:
  using value_type = typename Base::value_type;
  using pointer_type = typename Base::pointer_type;
  using const_pointer_type = typename Base::const_pointer_type;
  using reference_type = typename Base::reference_type;
  using const_reference_type = typename Base::const_reference_type;

  using Base::operator*;
  using Base::operator->;
  Node() {
    std::generate(children.begin(), children.end(), [] {return nullptr;});
  }
  explicit Node(value_type value) : Leaf<T, ChildCount>(value) {
    std::generate(children.begin(), children.end(), [] {return nullptr;});
  }
  Node(const Node &other) : Leaf<T, ChildCount>(other), children(other.children) {}
  Node &operator=(const Node &other) {
    if (&other == this) {
      return *this;
    }
    *this = Leaf<T, ChildCount>::operator=(other);
    children = other.children;
    return *this;
  }
  Node(Node &&other) noexcept : Leaf<T, ChildCount>(other), children(std::move(other.children)) {}
  Node &operator=(Node &&other) noexcept {
    *this = Leaf<T, ChildCount>::operator=(other);
    children = std::move(other.children);
    return *this;
  }

  bool hasChildAtIndex(std::size_t index) {
    assert(index < ChildCount);
    return children[index] != nullptr;
  }

  Child &setChildAtIndex(std::size_t index, NodeType nodeType) {
    if (nodeType == NodeType::Leaf) {
      children[index] = std::make_unique<Leaf<T, ChildCount>>();
    } else if (nodeType == NodeType::Node) {
      children[index] = std::make_unique<Node>();
    }
    return *children[index];
  }

  Child &childAtIndex(std::size_t index) {
    assert(index < ChildCount);
    return *children[index];
  }

  Children &getChildren() {
    return children;
  }

  [[nodiscard]] NodeType getType() const override { return NodeType::Node; }

private:
  Children children;
};

template <typename T, unsigned int ChildCount>
class Tree {
public:
  using Root = Node<T, ChildCount>;
  using value_type = typename Root::value_type;
  using pointer_type = typename Root::pointer_type;
  using const_pointer_type = typename Root::const_pointer_type;
  using reference_type = typename Root::reference_type;
  using const_reference_type = typename Root::const_reference_type;

  Tree() = default;
  explicit Tree(value_type rootValue) : root(std::make_unique<Root>(rootValue)) {}

  Root &getRoot() {
    return *root;
  }

private:
  std::unique_ptr<Root> root;
};

#endif // UTILITIES_TREE_H
