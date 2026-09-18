#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cstring>

// ---------- Sort implementations ----------

void insertion_sort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = (int)i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& buf) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) buf[k++] = arr[i++];
        else buf[k++] = arr[j++];
    }
    while (i <= mid) buf[k++] = arr[i++];
    while (j <= right) buf[k++] = arr[j++];
    for (int x = left; x <= right; ++x) arr[x] = buf[x];
}

void merge_sort_impl(std::vector<int>& arr, int left, int right, std::vector<int>& buf) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_impl(arr, left, mid, buf);
    merge_sort_impl(arr, mid + 1, right, buf);
    merge(arr, left, mid, right, buf);
}

void merge_sort(std::vector<int>& arr) {
    std::vector<int> buf(arr.size());
    if (!arr.empty()) merge_sort_impl(arr, 0, (int)arr.size() - 1, buf);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_impl(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort_impl(arr, low, p - 1);
        quick_sort_impl(arr, p + 1, high);
    }
}

void quick_sort(std::vector<int>& arr) {
    if (!arr.empty()) quick_sort_impl(arr, 0, (int)arr.size() - 1);
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void std_sort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

// ---------- Benchmark harness ----------

using Clock = std::chrono::high_resolution_clock;

template <typename Func>
double time_sort(Func sort_fn, std::vector<int> arr) {
    // Note: arr is passed BY VALUE so each algorithm sorts a fresh unsorted copy.
    auto start = Clock::now();
    sort_fn(arr);
    auto end = Clock::now();
    // sanity check: confirm it's actually sorted
    if (!std::is_sorted(arr.begin(), arr.end())) {
        std::cerr << "ERROR: sort produced unsorted output!\n";
    }
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};
    const int trials = 3;

    std::mt19937 rng(42);

    std::cout << std::left
               << std::setw(10) << "Size"
               << std::setw(14) << "Insertion"
               << std::setw(12) << "Merge"
               << std::setw(12) << "Quick"
               << std::setw(12) << "Heap"
               << std::setw(12) << "std::sort"
               << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> base(n);
        std::uniform_int_distribution<int> dist(0, 1000000000);
        for (int i = 0; i < n; ++i) base[i] = dist(rng);

        double best_insertion = 1e18, best_merge = 1e18, best_quick = 1e18, best_heap = 1e18, best_std = 1e18;

        // Skip insertion sort for large n -- it's O(n^2) and would take far too long.
        bool run_insertion = (n <= 20000);

        for (int t = 0; t < trials; ++t) {
            if (run_insertion)
                best_insertion = std::min(best_insertion, time_sort(insertion_sort, base));
            best_merge = std::min(best_merge, time_sort(merge_sort, base));
            best_quick = std::min(best_quick, time_sort(quick_sort, base));
            best_heap  = std::min(best_heap,  time_sort(heap_sort, base));
            best_std   = std::min(best_std,   time_sort(std_sort, base));
        }

        std::cout << std::left << std::setw(10) << n;
        if (run_insertion)
            std::cout << std::setw(14) << best_insertion;
        else
            std::cout << std::setw(14) << "skipped";
        std::cout << std::setw(12) << best_merge
                   << std::setw(12) << best_quick
                   << std::setw(12) << best_heap
                   << std::setw(12) << best_std
                   << "\n";
    }

    std::cout << "\nAll times are milliseconds (best of " << trials << " trials). "
               << "Insertion sort skipped above 20000 elements (O(n^2) makes it impractical).\n";

    return 0;
}
