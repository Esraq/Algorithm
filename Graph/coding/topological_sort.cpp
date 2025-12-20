#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int V = 6;   // Number of vertices
    vector<vector<int>> adj(V);

    // Add directed edges
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    vector<int> indegree(V, 0);

    // Calculate indegree of each vertex
    for (int i = 0; i < V; i++) {
        for (int node : adj[i]) {
            indegree[node]++;
        }
    }

    // Queue for vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // Perform topological sort
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Output result
    cout << "Topological Order: ";
    for (int v : topo) {
        cout << v << " ";
    }

    return 0;
}
