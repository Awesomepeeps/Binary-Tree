#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum Color { RED, BLACK };

struct treeNode {
    int data;
    treeNode* left;
    treeNode* right;
    treeNode* parent;
    Color color;
    treeNode(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    treeNode* root;

    void leftRotate(treeNode* x) {
        treeNode* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(treeNode* y) {
        treeNode* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsertion(treeNode* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                treeNode* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
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
                treeNode* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
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

    void transplant(treeNode* u, treeNode* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    treeNode* minValueNode(treeNode* node) {
        treeNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void fixDeletion(treeNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                treeNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                treeNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void inorderHelper(treeNode* root, int level) {
        if (root != nullptr) {
            inorderHelper(root->right, level + 1);
            for (int i = 0; i < level; i++)
                cout << "   ";
            cout << root->data;
            if (root->color == RED)
                cout << " (Red)" << endl;
            else
                cout << " (Black)" << endl;
            inorderHelper(root->left, level + 1);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        treeNode* z = new treeNode(data);
        treeNode* y = nullptr;
        treeNode* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;
        z->left = nullptr;
        z->right = nullptr;
        z->color = RED;
        fixInsertion(z);
    }

    void remove(int data) {
        treeNode* z = root;
        treeNode* x, *y;
        while (z != nullptr) {
            if (z->data == data)
                break;
            if (z->data < data)
                z = z->right;
            else
                z = z->left;
        }
        if (z == nullptr) {
            cout << "Couldn't find key in the tree\n";
            return;
        }
        y = z;
        Color y_original_color = y->color;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minValueNode(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK)
            fixDeletion(x);
        delete z;
    }

    void search(int data) {
        treeNode* node = root;
        while (node != nullptr) {
            if (data == node->data) {
                cout << "Found: " << data << endl;
                return;
            } else if (data < node->data)
                node = node->left;
            else
                node = node->right;
        }
        cout << "Not Found: " << data << endl;
    }

    void inorder() {
        inorderHelper(root, 0);
    }
};

int main() {
    RedBlackTree rbt;
    string input;

    while (true) {
        cout << "Do you want to add, remove, print, search, or quit?" << endl;
        cin >> input;

        if (input == "add") {
            int num;
            cout << "Enter number to add: ";
            cin >> num;
            rbt.insert(num);
        } else if (input == "remove") {
            int num;
            cout << "Enter number to remove: ";
            cin >> num;
            rbt.remove(num);
        } else if (input == "print") {
            cout << "Inorder Traversal:" << endl;
            rbt.inorder();
            cout << endl;
        } else if (input == "search") {
            int num;
            cout << "Enter number to search: ";
            cin >> num;
            rbt.search(num);
        } else if (input == "quit") {
            break;
        }
    }

    return 0;
}
