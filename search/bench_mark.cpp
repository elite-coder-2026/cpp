#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

#include <iomanip>

// ---------- Search implementations ----------

int binary_search_impl(const std::vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int interpolation_search_impl(const std::vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (arr[high] == arr[low]) {
            return (arr[low] == target) ? low : -1;
        }
        int pos = low + (long long)(target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int exponential_search_impl(const std::vector<int>& arr, int target) {
    int n = (int)arr.size();
    if (n == 0) return -1;
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < n && arr[i] <= target) i *= 2;

    int low = i / 2;
    int high = std::min(i, n - 1);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ---------- Benchmark harness ----------

using Clock = std::chrono::high_resolution_clock;

template <typename Func>
double time_search(Func search_fn, const std::vector<int>& arr, const std::vector<int>& targets) {
    // Run once to warm cache, then time the batch of lookups.
    auto start = Clock::now();
    volatile int sink = 0; // prevent optimizing the calls away
    for (int t : targets) {
        sink += search_fn(arr, t);
    }
    auto end = Clock::now();
    (void)sink;
    return std::chrono::duration<double, std::micro>(end - start).count();
}

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    const int num_queries = 10000;
    const int trials = 5;

    std::mt19937 rng(42);

    std::cout << std::left
               << std::setw(12) << "Size"
               << std::setw(18) << "Binary(us)"
               << std::setw(22) << "Interpolation(us)"
               << std::setw(18) << "Exponential(us)"
               << "\n";
    std::cout << std::string(70, '-') << "\n";

    for (int n : sizes) {
        // Build a sorted, uniformly distributed array (best case for interpolation search).
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 2; // evenly spaced values

        // Random targets that exist in the array (avoids skewing timing with misses).
        std::uniform_int_distribution<int> idx_dist(0, n - 1);
        std::vector<int> targets(num_queries);
        for (int i = 0; i < num_queries; ++i) targets[i] = arr[idx_dist(rng)];

        double best_binary = 1e18, best_interp = 1e18, best_exp = 1e18;
        for (int t = 0; t < trials; ++t) {
            best_binary = std::min(best_binary, time_search(binary_search_impl, arr, targets));
            best_interp = std::min(best_interp, time_search(interpolation_search_impl, arr, targets));
            best_exp    = std::min(best_exp,    time_search(exponential_search_impl, arr, targets));
        }

        std::cout << std::left << std::setw(12) << n
                   << std::setw(18) << best_binary
                   << std::setw(22) << best_interp
                   << std::setw(18) << best_exp
                   << "\n";
    }

    std::cout << "\nAll times are microseconds for " << num_queries
               << " lookups (best of " << trials << " trials).\n";

    return 0;
}
