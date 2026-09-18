#include <iostream>
#include <vector>


bool dfs(std::vector<std::vector<int>>& adj, int u,
         std::vector<bool>& visited, std::vector<bool>& recStack) {

    // Node is already in the current DFS path
    if (recStack[u])
        return true;

    // Node is already visited
    if (visited[u])
        return false;

    visited[u] = true;
    recStack[u] = true;

    // Visit all adjacent nodes
    for (int v : adj[u]) {
        if (dfs(adj, v, visited, recStack))
            return true;
    }

    // Remove node from current DFS path
    recStack[u] = false;

    return false;
}

bool isCyclic(int V, std::vector<std::vector<int>>& edges) {

    vector<vector<int>> adj(V);

    // Create adjacency list
    for (auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
    }

    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    // Check all components
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dfs(adj, i, visited, recStack))
            return true;
    }

    return false;
}

int main() {

    int V = 4;

    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 0},
        {2, 3}
    };

    cout << (isCyclic(V, edges) ? "true" : "false") << endl;

    return 0;
}
