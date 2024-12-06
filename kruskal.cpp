#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find the subset of an element (with path compression)
int findSubset(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = findSubset(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to union two subsets (by rank)
void unionSubsets(vector<Subset>& subsets, int x, int y) {
    int xRoot = findSubset(subsets, x);
    int yRoot = findSubset(subsets, y);

    if (subsets[xRoot].rank < subsets[yRoot].rank) {
        subsets[xRoot].parent = yRoot;
    } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
        subsets[yRoot].parent = xRoot;
    } else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

// Function to compare two edges based on their weights
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Kruskal's algorithm to find MST
void kruskalMST(vector<Edge>& edges, int V) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Create subsets for union-find
    vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> mst; // To store the edges of the MST

    for (const auto& edge : edges) {
        int x = findSubset(subsets, edge.src);
        int y = findSubset(subsets, edge.dest);

        // If including this edge does not form a cycle
        if (x != y) {
            mst.push_back(edge);
            unionSubsets(subsets, x, y);
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    int totalWeight = 0;
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of the Minimum Spanning Tree: " << totalWeight << endl;
}

// Driver Code
int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter the edges (src dest weight):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    kruskalMST(edges, V);

    return 0;
}
