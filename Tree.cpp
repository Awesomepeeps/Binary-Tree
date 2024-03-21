#include <iostream>
using namespace std;

struct treeNode {
    int data;
    treeNode* left;
    treeNode* right;
    treeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

class binaryTree {
private:
    treeNode* root;

    treeNode* insert(treeNode* node, int data) {
        if (node == nullptr) {
            return new treeNode(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }

        return node;
    }

    treeNode* findMin(treeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    treeNode* remove(treeNode* node, int data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                treeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                treeNode* temp = node->left;
                delete node;
                return temp;
            } else {
                treeNode* successor = findMin(node->right);
                node->data = successor->data;
                node->right = remove(node->right, successor->data);
            }
        }
        return node;
    }

    bool search(treeNode* node, int data) {
        if (node == nullptr) {
            return false;
        }
        if (data == node->data) {
            return true;
        }
        if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

    void print(treeNode* node, int depth) {
        if (node == nullptr) {
            return;
        }
        print(node->right, depth + 1);
        for (int i = 0; i < depth; ++i) {
            cout << "   ";
        }
        cout << node->data << endl;
        print(node->left, depth + 1);
    }

public:
    binaryTree() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    bool search(int data) {
        return search(root, data);
    }

    void print() {
        print(root, 0);
    }
};

int main() {
    binaryTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);

    cout << "binaryTree after initial insertion:" << endl;
    bst.print();
    cout << endl;

    bst.remove(30);

    cout << "binaryTree after removing 30:" << endl;
    bst.print();
    cout << endl;

    int num = 40;
    cout << num << " is " << (bst.search(num) ? "found" : "not found") << " in the binaryTree." << endl;

    return 0;
}
