# Traveling Salesperson Problem (TSP)

## The Problem
Given a set of cities and the distance between every pair, find the shortest route that visits each city exactly once and returns to the starting city.

TSP is **NP-hard**: no known algorithm solves every instance in polynomial time.

## Approaches

### 1. Brute Force
Try every possible ordering of cities and keep the shortest.

- Fix a start city, permute the remaining `n-1` cities.
- Time: **O(n!)**. Fine for n ≤ ~10, unusable beyond that.

### 2. Dynamic Programming (Held-Karp)
Avoid recomputing shared subpaths.

- State: `dp[mask][i]` = shortest path that starts at city 0, visits exactly the cities in bitmask `mask`, and ends at city `i`.
- Base: `dp[1][0] = 0`.
- Transition: `dp[mask][i] = min over j in mask, j != i of dp[mask without i][j] + dist[j][i]`.
- Answer: `min over i of dp[full][i] + dist[i][0]`.
- Time: **O(n² · 2ⁿ)**, Space: **O(n · 2ⁿ)**. Practical up to n ≈ 20-25.

### 3. Nearest Neighbor (Greedy Heuristic)
1. Start at any city.
2. Repeatedly move to the closest unvisited city.
3. Return to the start.

- Time: **O(n²)**.
- Fast, but not optimal; can be far from the best tour.

### 4. Other Heuristics / Approximations
- **2-opt / 3-opt**: repeatedly remove 2 (or 3) edges and reconnect them if it shortens the tour.
- **Christofides**: for metric TSP (triangle inequality holds), guarantees a tour within **1.5×** optimal.
- **MST-based 2-approximation**: build a minimum spanning tree, walk it in preorder; within **2×** optimal for metric TSP.
- **Simulated annealing, genetic algorithms, ant colony**: metaheuristics that give good tours on large inputs.

### 5. Exact Solvers for Large Instances
Branch and bound and branch-and-cut (e.g., Concorde) use linear programming to solve instances with thousands of cities.

## Comparison

| Method          | Time            | Optimal? | Practical size   |
|-----------------|-----------------|----------|------------------|
| Brute force     | O(n!)           | Yes      | ~10              |
| Held-Karp DP    | O(n² · 2ⁿ)      | Yes      | ~20-25           |
| Nearest neighbor| O(n²)           | No       | Very large       |
| 2-opt           | ~O(n²) per pass | No       | Large            |
| Christofides    | O(n³)           | No (1.5×)| Large            |

## C++ Sketch (Held-Karp)

```cpp
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int tsp(const vector<vector<int>>& dist) {
    int n = dist.size();
    int full = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    dp[1][0] = 0;

    for (int mask = 1; mask <= full; mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) || dp[mask][i] == INT_MAX) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                int next = mask | (1 << j);
                dp[next][j] = min(dp[next][j], dp[mask][i] + dist[i][j]);
            }
        }
    }

    int best = INT_MAX;
    for (int i = 1; i < n; i++)
        if (dp[full][i] != INT_MAX)
            best = min(best, dp[full][i] + dist[i][0]);
    return best;
}
```

## Real-World Uses
Delivery routing, circuit board drilling, DNA sequencing, telescope scheduling, and logistics planning.
