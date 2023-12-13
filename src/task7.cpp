#include <iostream>
#include <unordered_map>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data) : data(data) {
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;
    std::unordered_map<int, int> blackHeight;

    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }

        rightChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }

        leftChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsertion(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    int calculateBlackHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = calculateBlackHeight(node->left);
        int rightHeight = calculateBlackHeight(node->right);

        int currentHeight = (node->color == BLACK) ? 1 : 0;
        int maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;

        return currentHeight + maxHeight;
    }

    void calculateAndDisplayBlackHeight(Node* node) {
        if (node == nullptr) {
            return;
        }

        int height = calculateBlackHeight(node);
        blackHeight[node->data] = height;

        calculateAndDisplayBlackHeight(node->left);
        calculateAndDisplayBlackHeight(node->right);
    }

    void printTreeHelper(Node* node) {
        if (node == nullptr) {
            return;
        }

        printTreeHelper(node->right);
        std::cout << node->data << " ";
        printTreeHelper(node->left);
    }

    Node* searchNode(Node* node, int data) {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return searchNode(node->left, data);
        } else {
            return searchNode(node->right, data);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(int data) {
        Node* newNode = new Node(data);
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        } else if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsertion(newNode);
    }

    void search(int data) {
        Node* node = searchNode(root, data);

        if (node != nullptr) {
            int height = blackHeight[node->data];
            std::cout << node->data << " is found, its height is " << height << std::endl;
        } else {
            std::cout << data << " is not found" << std::endl;
        }
    }

    void printTree() {
        calculateAndDisplayBlackHeight(root);
        printTreeHelper(root);
    }
};

int main() {
    int N;
    std::cin >> N;

    RedBlackTree tree;

    for (int i = 0; i < N; i++) {
        int value;
        std::cin >> value;
        tree.Insert(value);
    }

    int searchValue;
    std::cin >> searchValue;

    tree.search(searchValue);

    return 0;
}