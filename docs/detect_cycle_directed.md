# Detect Cycle in a Directed Graph

## The Problem
Given a directed graph, determine whether it contains a cycle, meaning a path that starts and ends at the same vertex by following edge directions.

Example: `0 → 1 → 2 → 0` is a cycle. `0 → 1 → 2` and `0 → 2` is not.

A directed graph with no cycle is a **DAG** (directed acyclic graph). Cycle detection is required for topological sorting, dependency resolution, deadlock detection, and build systems.

## Why Undirected Cycle Detection Doesn't Work Here
In an undirected graph, revisiting any visited vertex other than the parent means a cycle. In a directed graph, reaching an already-visited vertex is not enough: two different paths can reach the same vertex without forming a cycle (e.g., `0→1, 0→2, 1→3, 2→3`). We need to know whether the visited vertex is on the **current path**.

## Approach 1: DFS with Recursion Stack

Track three states per vertex:

| State | Meaning |
|-------|---------|
| White (0) | Not visited |
| Gray (1) | Visited and still on the current DFS path |
| Black (2) | Fully processed (all descendants explored) |

Algorithm:
1. For each unvisited vertex, start a DFS.
2. On entering a vertex, mark it gray.
3. For each neighbor:
   - Gray → **back edge found, cycle exists**.
   - White → recurse.
   - Black → skip (already known to be safe).
4. On leaving, mark the vertex black.

Time: **O(V + E)**. Space: **O(V)** for the state array and recursion stack.

### C++ Implementation

```cpp
#include <vector>
using namespace std;

bool dfs(int u, const vector<vector<int>>& adj, vector<int>& state) {
    state[u] = 1;                       // gray: on current path
    for (int v : adj[u]) {
        if (state[v] == 1) return true; // back edge -> cycle
        if (state[v] == 0 && dfs(v, adj, state)) return true;
    }
    state[u] = 2;                       // black: done
    return false;
}

bool hasCycle(int n, const vector<vector<int>>& adj) {
    vector<int> state(n, 0);
    for (int i = 0; i < n; i++)
        if (state[i] == 0 && dfs(i, adj, state))
            return true;
    return false;
}
```

## Approach 2: Kahn's Algorithm (BFS Topological Sort)

1. Compute the in-degree of every vertex.
2. Push all vertices with in-degree 0 into a queue.
3. Pop a vertex, count it as processed, and decrement the in-degree of its neighbors; push any that reach 0.
4. If the number of processed vertices is less than `V`, the remaining vertices are in a cycle.

Time: **O(V + E)**. Space: **O(V)**.

```cpp
#include <vector>
#include <queue>
using namespace std;

bool hasCycleKahn(int n, const vector<vector<int>>& adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);

    int processed = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        processed++;
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return processed != n;
}
```

## Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| DFS (3-color) | O(V + E) | O(V) | Can also recover the cycle path; deep recursion on large graphs |
| Kahn's (BFS) | O(V + E) | O(V) | Iterative; also yields a topological order when acyclic |

## Edge Cases
- Self-loop (`u → u`) is a cycle. Both approaches catch it.
- Disconnected graphs: DFS must be started from every unvisited vertex.
- Empty graph or a single vertex with no edges: no cycle.
- Very deep graphs may overflow the recursion stack; prefer Kahn's or an iterative DFS.
