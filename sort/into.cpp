#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cstring>

#include <string>
#include <memory>

// ---------- Sort algorithms as classes ----------

class ISortAlgorithm {
public:
    virtual ~ISortAlgorithm() = default;
    virtual void sort(std::vector<int>& arr) const = 0;
    virtual std::string name() const = 0;
};

class InsertionSort : public ISortAlgorithm {
public:
    void sort(std::vector<int>& arr) const override {
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
    std::string name() const override { return "Insertion"; }
};

class MergeSort : public ISortAlgorithm {
public:
    void sort(std::vector<int>& arr) const override {
        std::vector<int> buf(arr.size());
        if (!arr.empty()) merge_sort_impl(arr, 0, (int)arr.size() - 1, buf);
    }
    std::string name() const override { return "Merge"; }

private:
    static void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& buf) {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) buf[k++] = arr[i++];
            else buf[k++] = arr[j++];
        }
        while (i <= mid) buf[k++] = arr[i++];
        while (j <= right) buf[k++] = arr[j++];
        for (int x = left; x <= right; ++x) arr[x] = buf[x];
    }

    static void merge_sort_impl(std::vector<int>& arr, int left, int right, std::vector<int>& buf) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        merge_sort_impl(arr, left, mid, buf);
        merge_sort_impl(arr, mid + 1, right, buf);
        merge(arr, left, mid, right, buf);
    }
};

class QuickSort : public ISortAlgorithm {
public:
    void sort(std::vector<int>& arr) const override {
        if (!arr.empty()) quick_sort_impl(arr, 0, (int)arr.size() - 1);
    }
    std::string name() const override { return "Quick"; }

private:
    static int partition(std::vector<int>& arr, int low, int high) {
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

    static void quick_sort_impl(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int p = partition(arr, low, high);
            quick_sort_impl(arr, low, p - 1);
            quick_sort_impl(arr, p + 1, high);
        }
    }
};

class HeapSort : public ISortAlgorithm {
public:
    void sort(std::vector<int>& arr) const override {
        int n = (int)arr.size();
        for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    std::string name() const override { return "Heap"; }

private:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) largest = l;
        if (r < n && arr[r] > arr[largest]) largest = r;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

class StdSort : public ISortAlgorithm {
public:
    void sort(std::vector<int>& arr) const override {
        std::sort(arr.begin(), arr.end());
    }
    std::string name() const override { return "std::sort"; }
};

// ---------- Benchmark harness as a class ----------

class SortBenchmark {
public:
    using Clock = std::chrono::high_resolution_clock;

    SortBenchmark(std::vector<int> sizes, int trials, unsigned seed)
        : sizes_(std::move(sizes)), trials_(trials), rng_(seed) {
        algorithms_.push_back(std::make_unique<InsertionSort>());
        algorithms_.push_back(std::make_unique<MergeSort>());
        algorithms_.push_back(std::make_unique<QuickSort>());
        algorithms_.push_back(std::make_unique<HeapSort>());
        algorithms_.push_back(std::make_unique<StdSort>());
    }

    void run() {
        printHeader();
        for (int n : sizes_) {
            runForSize(n);
        }
        std::cout << "\nAll times are milliseconds (best of " << trials_ << " trials). "
                   << "Insertion sort skipped above 20000 elements (O(n^2) makes it impractical).\n";
    }

private:
    std::vector<int> sizes_;
    int trials_;
    std::mt19937 rng_;
    std::vector<std::unique_ptr<ISortAlgorithm>> algorithms_;

    void printHeader() const {
        std::cout << std::left
                   << std::setw(10) << "Size"
                   << std::setw(14) << "Insertion"
                   << std::setw(12) << "Merge"
                   << std::setw(12) << "Quick"
                   << std::setw(12) << "Heap"
                   << std::setw(12) << "std::sort"
                   << "\n";
        std::cout << std::string(72, '-') << "\n";
    }

    double timeSort(const ISortAlgorithm& algo, std::vector<int> arr) const {
        // arr is passed BY VALUE so each algorithm sorts a fresh unsorted copy.
        auto start = Clock::now();
        algo.sort(arr);
        auto end = Clock::now();
        if (!std::is_sorted(arr.begin(), arr.end())) {
            std::cerr << "ERROR: " << algo.name() << " sort produced unsorted output!\n";
        }
        return std::chrono::duration<double, std::milli>(end - start).count();
    }

    void runForSize(int n) {
        std::vector<int> base(n);
        std::uniform_int_distribution<int> dist(0, 1000000000);
        for (int i = 0; i < n; ++i) base[i] = dist(rng_);

        bool run_insertion = (n <= 20000);

        // best_times[i] corresponds to algorithms_[i]
        std::vector<double> best_times(algorithms_.size(), 1e18);

        for (int t = 0; t < trials_; ++t) {
            for (size_t i = 0; i < algorithms_.size(); ++i) {
                if (!run_insertion && algorithms_[i]->name() == "Insertion") continue;
                double result = timeSort(*algorithms_[i], base);
                best_times[i] = std::min(best_times[i], result);
            }
        }

        std::cout << std::left << std::setw(10) << n;
        for (size_t i = 0; i < algorithms_.size(); ++i) {
            int width = (algorithms_[i]->name() == "Insertion") ? 14 : 12;
            if (!run_insertion && algorithms_[i]->name() == "Insertion")
                std::cout << std::setw(width) << "skipped";
            else
                std::cout << std::setw(width) << best_times[i];
        }
        std::cout << "\n";
    }
};

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};
    const int trials = 3;
    const unsigned seed = 42;

    SortBenchmark benchmark(sizes, trials, seed);
    benchmark.run();

    return 0;
}
