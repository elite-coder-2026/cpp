


#include <vector>




class Sort {
public:
    void insertion_sort(std::vector<int>& arr);
    void merge_sort(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& buf);
    void merge_util(std::vector<int>& arr, int left, int right, std::vector<int>&buf);
    void _merge(std::vector<int>& arr);
};
