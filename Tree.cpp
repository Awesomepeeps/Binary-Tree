#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct treeNode {
    int data;
    treeNode* left;
    treeNode* right;
    treeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

class binaryTree { // idea of implementation came from geekforgeek
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
    string input;

    while (true) {
        cout << "Do you want to add, remove, print, search, or quit?" << endl;
        cin >> input;

        if (input == "add") {
            string terfl;
            cout << "Terminal or file?";
            cin >> terfl;
            if (terfl == "terminal") {
                int num;
                cout << "Enter number to add: ";
                cin >> num;
                bst.insert(num);
            }
            else if (terfl == "file") {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                ifstream inputFile(filename);
                if (inputFile.is_open()) {
                    int num;
                    while (inputFile >> num) {
                        bst.insert(num);
                    }
                    inputFile.close();
                }
                else {
                    cout << "No file exists" << endl;
                }
            }
        }
        else if (input == "remove") {
            int num;
            cout << "Enter number to remove: ";
            cin >> num;
            bst.remove(num);
        }
        else if (input == "print") {
            cout << "Binary Search Tree:" << endl;
            bst.print();
        }
        else if (input == "search") {
            int num;
            cout << "Enter number to search: ";
            cin >> num;
            if (bst.search(num)) {
                cout << num << " is found in the tree." << endl;
            } 
            else {
                cout << num << " is not found in the tree." << endl;
            }        
        }
        else if (input == "quit") {
            break;
        }
    }
}