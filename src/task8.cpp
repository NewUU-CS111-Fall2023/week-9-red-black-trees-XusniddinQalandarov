#include <iostream>
#include <vector>

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left, *right, *parent;

    Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void insertFixup(Node* z);

public:
    RedBlackTree();
    void insert(int key);
    void inOrderTraversal(Node* node, std::vector<int>& result);
    void median();
};

RedBlackTree::RedBlackTree() {
    NIL = new Node(0);
    NIL->color = BLACK;
    root = NIL;
}

void RedBlackTree::leftRotate(Node* x) {
    // Left rotation of nodes in a Red-Black Tree
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
    // Right rotation of nodes in a Red-Black Tree
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void RedBlackTree::insertFixup(Node* z) {
    // Fix the Red-Black Tree properties after insertion
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(int key) {
    // Insert a key into the Red-Black Tree
    Node* z = new Node(key);
    Node* y = NIL;
    Node* x = root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NIL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFixup(z);
}

void RedBlackTree::inOrderTraversal(Node* node, std::vector<int>& result) {
    // In-order traversal to get sorted elements
    if (node != NIL) {
        inOrderTraversal(node->left, result);
        result.push_back(node->key);
        inOrderTraversal(node->right, result);
    }
}

void RedBlackTree::median() {
    // Find and print the median of the Red-Black Tree
    std::vector<int> sortedElements;
    inOrderTraversal(root, sortedElements);

    int n = sortedElements.size();
    if (n % 2 == 0) {
        int medianIndex1 = n / 2 - 1;
        int medianIndex2 = n / 2;
        int medianValue = (sortedElements[medianIndex1] + sortedElements[medianIndex2]) / 2;
        std::cout << medianValue << " is median" << std::endl;
    } else {
        int medianIndex = n / 2;
        int medianValue = sortedElements[medianIndex];
        std::cout << medianValue << " is median" << std::endl;
    }
}

int main() {
    RedBlackTree tree;
    
    int N, value;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        std::cin >> value;
        tree.insert(value);
    }

    tree.median();

    return 0;
}
