
# ifndef SORTS_H
# define SORTS_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
arr_element tmp_space[10000005];
# endif


#include <algorithm>

typedef void (*SORT_FUNCP)(arr_element[],const int);


namespace sorts
{
    void primitive_insertion_sort (arr_element arr[], const int len)
    {
        int tmp, j;
        for (int i = 1; i < len; i++) {
            tmp = arr[i];
            j = i - 1;
            while (j >= 0 && tmp < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = tmp;
        }
    }

    void primitive_merge_sort (arr_element arr[], const int len)
    {
        static arr_element *tmp_arr = tmp_space;

        if (len < 2)
            return ;

        int m = len >> 1, l = 0, r = m, pi =0;

        primitive_merge_sort(arr, m);
        primitive_merge_sort(arr + m, len - m);

        while (l < m && r < len) {
            tmp_arr[pi++] = (arr[l] < arr[r]) ? arr[l++] : arr[r++];
        }
        while (l < m) {
            tmp_arr[pi++] = arr[l++];
        }
        while (r < len) {
            tmp_arr[pi++] = arr[r++];
        }

        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
        }
    }

    int hoare_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        for(int l = 0,r = len - 1;;) {
            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                return l;
            }
            std::swap(arr[l], arr[r]);
        }
    }

    int lomuto_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        int l = 0;
        for(int i = 1; i < len; i++) {
            if (arr[i] <= pivot) {
                l++;
                std::swap(arr[l], arr[i]);
            }
        }
        std::swap(arr[0], arr[l]);
        return l;
    }

    int hoare_partition_with_median_of_three (arr_element arr[], const int len)
    {
        int m = len >> 1;
        if (arr[len - 1] < arr[0]) {
            std::swap(arr[len - 1], arr[0]);
        }
        if (arr[len - 1] < arr[m]) {
            std::swap(arr[len - 1], arr[m]);
        }
        if (arr[m] < arr[0]) {
            std::swap(arr[m], arr[0]);
        }

        arr_element pivot = arr[0];
        for(int l = 0,r = len - 1;;) {
            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                return l;
            }
            std::swap(arr[l], arr[r]);
        }
    }

    void hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = hoare_partition(arr, len);
        hoare_quick_sort(arr, pivot);
        hoare_quick_sort(arr + pivot + 1, len - pivot - 1);
    }

    void hoare_quick_sort_with_median_of_three (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = hoare_partition_with_median_of_three(arr, len);
        hoare_quick_sort_with_median_of_three(arr, pivot);
        hoare_quick_sort_with_median_of_three(arr + pivot + 1, len - pivot - 1);
    }

    void lomuto_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = lomuto_partition(arr, len);
        lomuto_quick_sort(arr, pivot);
        lomuto_quick_sort(arr + pivot + 1, len - pivot - 1);
    }

    void random_hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        std::random_shuffle(arr, arr+len);
        hoare_quick_sort(arr, len);
    }
}

# endif