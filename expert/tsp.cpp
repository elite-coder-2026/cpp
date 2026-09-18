#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int tsp(std::vector<std::vector<int>>& cost) {
    int num_nodes = cost.size();
    std::vector<int> nodes;

    for (int i = 1; i < num_nodes; i++) {
        nodes.push_back(i);
    }

    int minCost = INT_MAX;
    int curr_node = 0;

    do {
        int curr = 0;

        for (int i = 0; i < nodes.size(); i++) {
            curr += cost[curr][nodes[i]];
            curr = nodes[i];
        }

        curr += cost[curr_node][0];

        minCost = fmin(minCost, curr);
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    return minCost;
}

int main() {
    std::vector<std::vector<int>> cost = {{0, 10, 15, 20},
                                          {10, 0, 35, 25},
                                          {15, 35, 0, 30},
                                          {20, 25, 30, 0}};

    int res = tsp(cost);

    std::cout << res << std::endl;

    return 0;
}
