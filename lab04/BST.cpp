// Lab 3 - BST_skeleton.cpp - rename it to BST.cpp
// Author: Colin Jamison

#include <limits.h>
#include <iostream>
#include <vector>
#include "BST.h"

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

std::shared_ptr<Node> BST::minimum() { return nullptr; }

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n) { return nullptr; }

std::shared_ptr<Node> BST::maximum() { return nullptr; }

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n) { return nullptr; }

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

void BST::deleteValue(int val) {}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val) { return nullptr; }

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
