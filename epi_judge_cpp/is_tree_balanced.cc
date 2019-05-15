#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct BalancedWithHeight {
  int height;
  bool isBalanced;
};
BalancedWithHeight TreeHeight(const unique_ptr<BinaryTreeNode<int>>& root) {
  if (root == nullptr) {
    return {0, true};
  }
  BalancedWithHeight leftHeight = TreeHeight(root->left);
  if (leftHeight.isBalanced) {
    auto rightHeight = TreeHeight(root->right);
    if (rightHeight.isBalanced) {
      return {1+std::max(leftHeight.height, rightHeight.height), std::abs(leftHeight.height-rightHeight.height) < 2};
    }
  }
  return {0, false};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& root) {
  if (root == nullptr) {
    return true;
  }

  auto leftHeight = TreeHeight(root->left);
  auto rightHeight = TreeHeight(root->right);
  if (!leftHeight.isBalanced || !rightHeight.isBalanced) {
    return false;
  }
  return std::abs(leftHeight.height - rightHeight.height) < 2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
