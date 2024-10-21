// Lab 5 Skeleton - rename it to "AVLTree.cpp"

#include "AVLTree.h"

#include <limits.h>

#include <iostream>


using namespace std;

// do not change anything in the above
// implement the following methods, starting here, do not add new functions

AVLTree::AVLTree() {}

std::shared_ptr<AVLNode> AVLTree::getRoot() { return this->root; }

int AVLTree::getSize() {
    vector<std::shared_ptr<AVLNode>> order;
    inOrder(this->root, order);
    return order.size();
}

std::shared_ptr<AVLNode> AVLTree::search(int val) {
    if (!this->root) {
        return nullptr;
    }

    if (this->root->value == val) {
        return this->root;
    } else {
        return search(this->root, val);
    }
}

std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val) {
    if (!n) {
        return nullptr;
    }

    if (n->value < val) {
        return search(n->right, val);
    } else if (n->value > val) {
        return search(n->left, val);
    } else {
        return n;
    }
}

std::shared_ptr<AVLNode> AVLTree::minimum() {
    if (!this->root) {
        return nullptr;
    }

    return minimum(this->root);
}

std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n) {
    if (!n->left) {
        return n;
    } else {
        return minimum(n->left);
    }
}

std::shared_ptr<AVLNode> AVLTree::maximum() {
    if (!this->root) {
        return nullptr;
    }

    return maximum(this->root);
}

std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n) {
    if (!n->right) {
        return n;
    } else {
        return maximum(n->right);
    }
}

int getHeight(std::shared_ptr<AVLNode> n) { return n == nullptr ? -1 : n->height; }

int getBalanceFactor(std::shared_ptr<AVLNode> n) {
    if (n == nullptr) {
        return 0;
    } else {
        return n->balanceFactor;
    }
}

void AVLTree::insertValue(int val) {
    if (this->root == nullptr) {
        this->root = std::shared_ptr<AVLNode>(new AVLNode(val));
    } else {
        this->root = insertValue(this->root, val);
    }
}

std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val) {
    if (n == nullptr) {
        return std::shared_ptr<AVLNode>(new AVLNode(val));
    } else if (val < n->value) {
        n->left = insertValue(n->left, val);
    } else if (val > n->value) {
        n->right = insertValue(n->right, val);
    }

    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    n->balanceFactor = getHeight(n->right) - getHeight(n->left);
    n = rebalance(n);
    return n;
}

void AVLTree::deleteValue(int val) {
    if (this->root == nullptr) {
        return;
    }

    this->root = deleteValue(this->root, val);
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val) {
    if (n == nullptr) {
        return nullptr;
    }

    if (val < n->value) {
        n->left = deleteValue(n->left, val);
    } else if (val > n->value) {
        n->right = deleteValue(n->right, val);
    } else {
        if (n->left == nullptr && n->right == nullptr) {
            return nullptr;
        }

        if (n->left == nullptr) {
            return n->right;
        }
        if (n->right == nullptr) {
            return n->left;
        }

        int min = minimum(n->right)->value;
        n->value = min;
        n->right = deleteValue(n->right, min);
    }

    // Ensure the tree is balanced after deletion
    return rebalance(n);
}

std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n) {
  if (n->balanceFactor == 2) {
    if (n->right->balanceFactor >= 0) {
      return rotateLeft(n);
    } else {
      return rotateRightLeft(n);
    }
  } else if (n->balanceFactor == -2) {
    if (n->left->balanceFactor <= 0) {
      return rotateRight(n);
    } else {
      return rotateLeftRight(n);
    }
  }

  return n;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n) {
    auto newRoot = n->right;
    n->right = newRoot->left;
    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    n->balanceFactor = getHeight(n->left) - getHeight(n->right);

    newRoot->left = n;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->balanceFactor = getHeight(newRoot->right) - getHeight(newRoot->left);

    return newRoot;
}

std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n) {
    auto newRoot = n->left;
    if (!newRoot) return nullptr;
    n->left = newRoot->right;
    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    n->balanceFactor = getHeight(n->left) - getHeight(n->right);

    newRoot->right = n;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->balanceFactor = getHeight(newRoot->right) - getHeight(newRoot->left);

    return newRoot;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n) {
    if (!n) return nullptr;

    // Perform right rotation on the left child
    n->left = rotateRight(n->left);

    // Perform left rotation on the node
    return rotateLeft(n);
}

std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n) {
    if (!n) return nullptr;

    // Perform left rotation on the right child
    n->right = rotateLeft(n->right);

    // Perform right rotation on the node
    return rotateRight(n);
}

void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>>& order) {
    if (n != nullptr) {
        order.push_back(n);
        preOrder(n->left, order);
        preOrder(n->right, order);
    }
}

void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>>& order) {
    if (n != nullptr) {
        inOrder(n->left, order);
        order.push_back(n);
        inOrder(n->right, order);
    }
}

void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>>& order) {
    if (n != nullptr) {
        postOrder(n->left, order);
        postOrder(n->right, order);
        order.push_back(n);
    }
}
