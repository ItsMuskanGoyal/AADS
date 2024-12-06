#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Suffix Tree Node structure
struct SuffixTreeNode {
    unordered_map<char, SuffixTreeNode*> children;
    vector<int> suffixIndices; // Store indices where suffix starts

    // Destructor to free memory
    ~SuffixTreeNode() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};

// Suffix Tree class
class SuffixTree {
private:
    SuffixTreeNode* root;
    string text;

    // Insert a suffix into the tree
    void insertSuffix(const string& suffix, int index) {
        SuffixTreeNode* current = root;
        for (char c : suffix) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new SuffixTreeNode();
            }
            current = current->children[c];
        }
        current->suffixIndices.push_back(index);
    }

public:
    // Constructor
    SuffixTree(const string& str) : text(str) {
        root = new SuffixTreeNode();
        buildSuffixTree();
    }

    // Destructor
    ~SuffixTree() {
        delete root;
    }

    // Build the suffix tree
    void buildSuffixTree() {
        for (int i = 0; i < text.length(); i++) {
            insertSuffix(text.substr(i), i);
        }
    }

    // Search for a pattern in the suffix tree
    vector<int> search(const string& pattern) {
        SuffixTreeNode* current = root;
        for (char c : pattern) {
            if (current->children.find(c) == current->children.end()) {
                return {}; // Pattern not found
            }
            current = current->children[c];
        }
        return current->suffixIndices;
    }

    // Display the suffix tree (debugging purposes)
    void display(SuffixTreeNode* node, string prefix) {
        for (auto& child : node->children) {
            cout << prefix << child.first << endl;
            display(child.second, prefix + child.first);
        }
    }

    // Display from the root
    void displayTree() {
        display(root, "");
    }
};

// Driver Code
int main() {
    string text;
    cout << "Enter the text: ";
    cin >> text;

    // Build the suffix tree
    SuffixTree tree(text);

    cout << "Suffix Tree built successfully!" << endl;

    // Display the suffix tree (for debugging)
    cout << "\nSuffix Tree Structure (Character paths):" << endl;
    tree.displayTree();

    string pattern;
    cout << "\nEnter the pattern to search: ";
    cin >> pattern;

    // Search for the pattern
    vector<int> result = tree.search(pattern);

    if (!result.empty()) {
        cout << "Pattern found at indices: ";
        for (int index : result) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found in the text." << endl;
    }

    return 0;
}

