#include <iostream>
#include <vector>
using namespace std;

// Function to compute the prefix table
vector<int> computePrefixTable(const string& pattern) {
    int m = pattern.length();
    vector<int> prefix(m, 0);
    int j = 0; // Length of the current prefix

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j - 1]; // Backtrack
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        prefix[i] = j;
    }

    return prefix;
}

// Function to perform KMP string matching
void KMPSearch(const string& text, const string& pattern) {
    vector<int> prefix = computePrefixTable(pattern);
    int n = text.length();
    int m = pattern.length();
    int j = 0; // Pointer for the pattern

    bool found = false;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = prefix[j - 1]; // Backtrack
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) { // Match found
            cout << "Pattern found at index " << i - m + 1 << endl;
            found = true;
            j = prefix[j - 1]; // Prepare for the next match
        }
    }

    if (!found) {
        cout << "Pattern not found in the text." << endl;
    }
}

// Driver Code
int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    KMPSearch(text, pattern);

    return 0;
}
