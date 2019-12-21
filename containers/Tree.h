//
// Created by petr on 12/21/19.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#ifndef UTILITIES_TREE_H
#define UTILITIES_TREE_H

#include <queue>
#include <utility>

enum class NodeType { Leaf, Node };

template <typename T, unsigned int ChildCount> class Leaf;
template <typename T, unsigned int ChildCount> class Node;
namespace detail {
template <typename T, unsigned int ChildCount, typename F>
void traverseDepthFirstImpl(Leaf<T, ChildCount> *node, F &callable);
template <typename T, unsigned int ChildCount, typename F>
void traverseDepthFirstIfImpl(Leaf<T, ChildCount> *node, F &callable);
template <typename T, unsigned int ChildCount, typename F>
void traverseBreadthFirstImpl(Leaf<T, ChildCount> *node, F &callable);
template <typename T, typename F>
void preorderImpl(Leaf<T, 2> *node, F &&callable);
template <typename T, typename F>
void inorderImpl(Leaf<T, 2> *node, F &&callable);
template <typename T, typename F>
void postorderImpl(Leaf<T, 2> *node, F &&callable);
} // namespace detail

template <typename T, unsigned int ChildCount> class Leaf {
public:
  using value_type = T;
  using pointer_type = T *;
  using const_pointer_type = const T *;
  using reference_type = T &;
  using const_reference_type = const T &;

  Leaf() = default;
  explicit Leaf(value_type value);
  Leaf(const Leaf &other);
  Leaf &operator=(const Leaf &other);
  Leaf(Leaf &&other) noexcept;
  Leaf &operator=(Leaf &&other) noexcept;

  reference_type operator*() { return value; }
  pointer_type operator->() { return &value; }

  const_reference_type getValue() const { return value; }
  void setValue(value_type value) { Leaf::value = value; }

  [[nodiscard]] virtual NodeType getType() const { return NodeType::Leaf; }

  template <typename F> void traverseDepthFirst(F &&callable);
  template <typename F> void traverseDepthFirstIf(F &&callable);
  template <typename F> void traverseBreadthFirst(F &&callable);

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

  template <unsigned int Count>
  static constexpr bool is_binary_tree = Count == 2;
  template <unsigned int Count>
  using enabled_for_binary = std::enable_if_t<is_binary_tree<Count>>;

public:
  using value_type = typename Base::value_type;
  using pointer_type = typename Base::pointer_type;
  using const_pointer_type = typename Base::const_pointer_type;
  using reference_type = typename Base::reference_type;
  using const_reference_type = typename Base::const_reference_type;

  using Base::operator*;
  using Base::operator->;
  Node();
  explicit Node(value_type value);
  Node(const Node &other);
  Node &operator=(const Node &other);
  Node(Node &&other) noexcept;
  Node &operator=(Node &&other) noexcept;

  bool hasChildAtIndex(std::size_t index);
  Child &setChildAtIndex(std::size_t index, NodeType nodeType);
  void setChildrenValues(const_reference_type value, NodeType nodeType);
  Child &childAtIndex(std::size_t index);
  Children &getChildren() { return children; }

  [[nodiscard]] NodeType getType() const override { return NodeType::Node; }

  template <unsigned int C = ChildCount, typename = enabled_for_binary<C>>
  Child &leftChild();
  template <unsigned int C = ChildCount, typename = enabled_for_binary<C>>
  Child &rightChild();

private:
  Children children;
};
template <typename T, unsigned int ChildCount> class Tree {
  template <unsigned int Count>
  static constexpr bool is_binary_tree = Count == 2;
  template <unsigned int Count>
  using enabled_for_binary = std::enable_if_t<is_binary_tree<Count>>;

public:
  using Root = Node<T, ChildCount>;
  using value_type = typename Root::value_type;
  using pointer_type = typename Root::pointer_type;
  using const_pointer_type = typename Root::const_pointer_type;
  using reference_type = typename Root::reference_type;
  using const_reference_type = typename Root::const_reference_type;

  Tree() = default;
  explicit Tree(value_type rootValue);

  static Tree BuildTree(std::size_t depth, const_reference_type initValue);

  Root &getRoot() { return *root; }

  // root->all of his children recursively
  template <typename F> void traverseDepthFirst(F &&callable);

  template <typename F> void traverseBreadthFirst(F &&callable);

  template <typename F> void traverseDepthFirstIf(F &&callable);

  template <typename F, unsigned int C = ChildCount,
            typename = enabled_for_binary<C>>
  void preorder(F &&callable);

  template <typename F, unsigned int C = ChildCount,
            typename = enabled_for_binary<C>>
  void inorder(F &&callable);

  template <typename F, unsigned int C = ChildCount,
            typename = enabled_for_binary<C>>
  void postorder(F &&callable);

private:
  std::unique_ptr<Root> root;

  static void initChildren(Node<T, ChildCount> *node,
                           const_reference_type initValue, std::size_t depth);
};

#include "containers/detail/Tree.tpp"
#include "containers/detail/Tree_detail.tpp"
#include "containers/detail/Tree_node.tpp"
#endif // UTILITIES_TREE_H

#pragma clang diagnostic pop