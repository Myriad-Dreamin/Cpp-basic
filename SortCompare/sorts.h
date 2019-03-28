
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

    int primitive_partition (arr_element arr[], const int len)
    {
        arr_element pivot_element = arr[0];
        for(int l = 0,r = len - 1;;) {
            while (l < r && arr[r] > pivot_element)r--;
            while (l < r && arr[l] <= pivot_element)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot_element;
                return l;
            }
            std::swap(arr[l], arr[r]);
        }
    }

    void primitive_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = primitive_partition(arr, len);
        primitive_quick_sort(arr, pivot);
        primitive_quick_sort(arr + pivot + 1, len - pivot - 1);
    }
}

# endif