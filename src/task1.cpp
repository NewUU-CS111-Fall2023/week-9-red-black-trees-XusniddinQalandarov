#include <iostream> 
 
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
 
    void printTreeHelper(Node* node) { 
        if (node == nullptr) { 
            return; 
        } 
 
        std::cout << "(" << node->data << "("; 
        if (node->color == RED) { 
            std::cout << "RED"; 
        } else { 
            std::cout << "BLACK"; 
        } 
        std::cout << ")"; 
        printTreeHelper(node->left); 
        printTreeHelper(node->right); 
        std::cout << ")"; 
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
 
    void printTree() { 
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
 
    tree.printTree(); 
 
    return 0; 
}
