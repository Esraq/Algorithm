#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
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
    graph[4] = {};

    bfs(0);
}
