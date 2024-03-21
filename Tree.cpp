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

    }

    treeNode* findMin(treeNode* node) {

    }

    treeNode* remove(treeNode* node, int data) {

    }

    bool search(treeNode* node, int data) {

    }

    void print(treeNode* node, int depth) {

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

}
