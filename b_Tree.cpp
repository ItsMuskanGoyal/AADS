#include <iostream>
using namespace std;

// A B-Tree node
class BTreeNode {
public:
    int *keys;         // Array of keys
    int t;             // Minimum degree (defines the range for number of keys)
    BTreeNode **C;     // Array of child pointers
    int n;             // Current number of keys
    bool leaf;         // True if leaf node

    // Constructor
    BTreeNode(int _t, bool _leaf);

    // Traversal function
    void traverse();

    // Search for a key in the subtree rooted at this node
    BTreeNode *search(int k);

    // Insert a new key into the subtree rooted at this node
    void insertNonFull(int k);

    // Split the child of this node
    void splitChild(int i, BTreeNode *y);

    // Friend class
    friend class BTree;
};

// A B-Tree
class BTree {
private:
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree

public:
    // Constructor
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    // Traverse the tree
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    // Search the tree for a key
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // Insert a new key
    void insert(int k);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    n = 0;
}

// Traverse all nodes in a subtree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) {
            C[i]->traverse();
        }
        cout << " " << keys[i];
    }

    if (!leaf) {
        C[i]->traverse();
    }
}

// Search for a key in a subtree
BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
    }

    if (keys[i] == k) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return C[i]->search(k);
}

// Insert a new key into the tree
void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k) i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

// Insert a new key into a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k) {
                i++;
            }
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Split a child node
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--) {
        C[j + 1] = C[j];
    }

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];

    n = n + 1;
}

// Driver Code
int main() {
    BTree t(3); // A B-Tree with minimum degree 3

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed B-Tree is: ";
    t.traverse();

    cout << "\nSearching for key 6: " << (t.search(6) != nullptr ? "Found" : "Not Found") << endl;
    cout << "Searching for key 15: " << (t.search(15) != nullptr ? "Found" : "Not Found") << endl;

    return 0;
}
