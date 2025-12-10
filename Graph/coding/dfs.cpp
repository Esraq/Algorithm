#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int node) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int main() {
    int n = 5; // number of nodes
    graph.resize(n);
    visited.resize(n, false);

    // example edges
    graph[0] = {1, 2};
    graph[1] = {0, 3};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {}; // isolated node

    dfs(0);
}
