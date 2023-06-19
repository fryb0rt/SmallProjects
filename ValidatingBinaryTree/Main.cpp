#include <vector>
#include <memory>

struct Tree {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
    };
    template<typename ...T>
    Node* add(T&& ... args) {
        storage_.push_back(std::make_unique<Node>(std::forward<decltype(args)>(args)...));
        return storage_.back().get();
    }
    Node* root = nullptr;
private:
    std::vector<std::unique_ptr<Node>> storage_;
};

/* Problem:
Given a binary tree, determine whether it is a complete binary tree.

A complete binary tree can only have missing nodes on the last level
and the nodes on the last level must be in their leftmost positions.
*/

void markOrdering(const Tree::Node* node, const int index, std::vector<bool>& ordering) {
    if (node != nullptr) {
        if (int(ordering.size()) <= index) {
            ordering.resize(index + 1, false);
        }
        ordering[index] = true;
        markOrdering(node->left, index * 2 + 1, ordering);
        markOrdering(node->right, index * 2 + 2, ordering);
    }
}
// Your solution:
bool is_complete_binary_tree(const Tree& tree) {
    std::vector<bool> ordering;
    markOrdering(tree.root, 0, ordering);
    for (const bool value : ordering) {
        if (!value) {
            return false;
        }
    }
    return true;
}

#include <cassert>

int main() {
    Tree tree;
    assert(is_complete_binary_tree(tree));

    tree.root = tree.add();
    assert(is_complete_binary_tree(tree));

    tree.root->left = tree.add();
    assert(is_complete_binary_tree(tree));

    tree.root->right = tree.add();
    assert(is_complete_binary_tree(tree));

    tree.root->left->left = tree.add();
    tree.root->left->right = tree.add();
    tree.root->right->left = tree.add();
    assert(is_complete_binary_tree(tree));

    Tree bad;
    bad.root = bad.add();
    bad.root->right = bad.add();
    assert(!is_complete_binary_tree(bad));

    bad.root->left = bad.add();
    bad.root->left->left = bad.add();
    bad.root->left->right = bad.add();
    bad.root->right->right = bad.add();
    assert(!is_complete_binary_tree(bad));
    return 0;
}