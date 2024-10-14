// Lab 3 - BST_skeleton.cpp - rename it to BST.cpp
// Author: Colin Jamison

#include "BST.h"

#include <limits.h>

#include <iostream>
#include <vector>

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

BST::BST() {}

BST::~BST() {}

std::shared_ptr<Node> BST::search(int target) {
    if (!this->root) {
        return nullptr;
    }

    if (this->root->value == target) {
        return this->root;
    } else {
        return search(this->root, target);
    }
}

std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target) {
    if (!n) {
        return nullptr;
    }

    if (n->value < target) {
        return search(n->right, target);
    } else if (n->value > target) {
        return search(n->left, target);
    } else {
        return n;
    }
}

std::shared_ptr<Node> BST::minimum() {
    if (!this->root) {
        return nullptr;
    }

    return minimum(this->root);
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n) {
    if (!n->left) {
        return n;
    } else {
        return minimum(n->left);
    }
}

std::shared_ptr<Node> BST::maximum() {
    if (!this->root) {
        return nullptr;
    }

    return maximum(this->root);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n) {
    if (!n->right) {
        return n;
    } else {
        return maximum(n->right);
    }
}

void BST::insertValue(int val) {
    if (this->root == nullptr) {
        this->root = std::shared_ptr<Node>(new Node(val));
    } else {
        this->root = insertValue(this->root, val);
    }
}

std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val) {
    if (val < n->value) {
        if (n->left != nullptr) {
            n->left = insertValue(n->left, val);
        } else {
            n->left = std::shared_ptr<Node>(new Node(val));
        }
    } else if (val > n->value) {
        if (n->right != nullptr) {
            n->right = insertValue(n->right, val);
        } else {
            n->right = std::shared_ptr<Node>(new Node(val));
        }
    }

    return n;
}

void BST::deleteValue(int val) {
    if (this->root == nullptr) {
        return;
    }

    this->root = deleteValue(this->root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val) {
    // If the current node is null, return null.
    if (n == nullptr) {
        return nullptr;
    }

    // Traverse the tree to find the node to delete.
    if (val < n->value) {
        n->left = deleteValue(n->left, val);
    } else if (val > n->value) {
        n->right = deleteValue(n->right, val);
    } else {
        // Node to be deleted found.

        // If the current node has no children, return null.
        if (n->left == nullptr && n->right == nullptr) {
            return nullptr;
        }

        // If the current node has one child, return the child.
        if (n->left == nullptr) {
            return n->right;
        }
        if (n->right == nullptr) {
            return n->left;
        }

        // If the current node has two children, find the minimum value in the right subtree.
        int min = minimum(n->right)->value;

        // Replace the current node's value with the minimum value in the right subtree.
        n->value = min;

        // Delete the minimum value in the right subtree.
        n->right = deleteValue(n->right, min);
    }

    return n;
}

bool BST::isBST(std::shared_ptr<Node> n) {
    if (n == nullptr) {
        return true;
    } else {
        return isBST(n, INT_MIN, INT_MAX);
    }
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high) {
    if (n == nullptr) {
        // An empty tree is technically a valid BST.
        return true;
    } else if (n->left == nullptr && n->right == nullptr) {
        // A single value is also a valid BST.
        return true;
    } else if (n->left == nullptr) {
        return isBST(n->right, n->value, high);
    } else if (n->right == nullptr) {
        return isBST(n->left, low, n->value);
    } else {
        return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);
    }
}

void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>>& order) {
    if (n != nullptr) {
        order.push_back(n);
        preOrder(n->left, order);
        preOrder(n->right, order);
    }
}

void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>>& order) {
    if (n != nullptr) {
        inOrder(n->left, order);
        order.push_back(n);
        inOrder(n->right, order);
    }
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>>& order) {
    if (n != nullptr) {
        postOrder(n->left, order);
        postOrder(n->right, order);
        order.push_back(n);
    }
}
