#include <iostream>
using namespace std;

// Definition of the Tree Node
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
class BinaryTree {
private:
    TreeNode* root;

    // Helper function for inserting a node
    TreeNode* insertNode(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else if (val > node->data) {
            node->right = insertNode(node->right, val);
        }

        return node;
    }

    // Helper function for searching a node
    bool searchNode(TreeNode* node, int val) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == val) {
            return true;
        }

        if (val < node->data) {
            return searchNode(node->left, val);
        } else {
            return searchNode(node->right, val);
        }
    }

    // Helper function for in-order traversal
    void inorderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    // Constructor
    BinaryTree() : root(nullptr) {}

    // Insert a new value into the tree
    void insert(int val) {
        root = insertNode(root, val);
    }

    // Search for a value in the tree
    bool search(int val) {
        return searchNode(root, val);
    }

    // Display the tree using in-order traversal
    void display() {
        cout << "In-order Traversal: ";
        inorderTraversal(root);
        cout << endl;
    }
};

// Driver Code
int main() {
    BinaryTree tree;

    // Insert values
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Display the tree
    tree.display();

    // Search for values
    int searchValue;
    cout << "Enter a value to search: ";
    cin >> searchValue;

    if (tree.search(searchValue)) {
        cout << searchValue << " is present in the tree." << endl;
    } else {
        cout << searchValue << " is not present in the tree." << endl;
    }

    return 0;
}
