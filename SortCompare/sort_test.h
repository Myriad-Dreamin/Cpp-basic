
# ifndef SORT_TEST_H
# define SORT_TEST_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


#include "tools.h"
#include "sorts.h"
#include <iostream>
#include <algorithm>


class Sort
{
protected:

    arr_element *arr;
    int arr_size;

    stop_watch self_watch;

    CsvHandle self_file;
    bool write_allowed;

    void prepare (arr_element const input_arr[], const int len)
    {
        if (len > arr_size) {
            throw std::invalid_argument("length to copy is out of range");
        }
        memcpy(arr, input_arr, sizeof(arr_element) * len);
    }

    void run (arr_element const input_arr[], const int len, SORT_FUNCP sort_func)
    {
        try {
            prepare(input_arr, len);
        } catch (...) {
            throw ;
        }

        begin_clock();
        sort_func(arr, len);
        end_clock();

        # ifdef DEBUG
        print_arr(arr, 10);
        assert_equal(test_space, std_space, len);
        # endif
    }
public:

    Sort (arr_element *your_space, const int space_size)
    {
        arr = your_space;
        arr_size = space_size;
        write_allowed = false;
    }

    Sort (arr_element *your_space, const int space_size, const char* file_path)
    {
        arr = your_space;
        arr_size = space_size;
        open(file_path);
    }

    inline void begin_clock ()
    {
        self_watch.start();
    }

    inline void end_clock ()
    {
        self_watch.stop();
    }

    inline void settle_clock ()
    {
        self_watch.clear();
    }

    void show (const time_unit t_unit=time_unit::musec)
    {
        using std::cout;
        using std::endl;
        switch(t_unit) {
            case time_unit::musec: {
                cout << "used " << self_watch.microsec() << " musec" << endl;
                break ;
            }
            case time_unit::misec: {
                cout << "used " << self_watch.millisec() << " misec" << endl;
                break ;
            }
            case time_unit::sec: {
                cout << "used " << self_watch.sec() << " sec" << endl;
                break ;
            }
            default: {
                throw std::invalid_argument(
                    "It is impossible reached? Did you input a wrong time_unit to show?"
                );
                break ;
            }
        }
    }

    double used_time (const time_unit t_unit=time_unit::musec)
    {
        switch(t_unit) {
            case time_unit::musec: {
                return self_watch.microsec();
                break ;
            }
            case time_unit::misec: {
                return self_watch.millisec();
                break ;
            }
            case time_unit::sec: {
                return self_watch.sec();
                break ;
            }
            default: {
                throw std::invalid_argument(
                    "It is impossible reached? Did you input a wrong time_unit to show?"
                );
                break ;
            }
        }
    }

    void open(const char *file_path)
    {
        self_file.open(file_path, std::ios::out | std::ios::app);
        write_allowed = true;
    }

    void close()
    {
        self_file.close();
        write_allowed = false;
    }

    void write_open()
    {
        write_allowed = true;
    }

    void write_close()
    {
        write_allowed = false;
    }

    void newline ()
    {
        self_file.newline();
    }

    template<typename T>
    void block(const T &out_element)
    {
        self_file.block(out_element);
    }
};


class InsertionSort: public Sort
{
public:
    InsertionSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    InsertionSort(
        arr_element *your_space,
        const int space_size,
        const char *file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_insertion_sort);
    }
};


class MergeSort: public Sort
{
private:
public:
    MergeSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    MergeSort(
        arr_element *your_space,
        const int space_size,
        const char *file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_merge_sort);
    }
};


class QuickSort: public Sort
{
public:
    QuickSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    QuickSort(
        arr_element *your_space,
        const int space_size,
        const char *file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        hoare(input_arr, len);
    }

    void hoare (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::hoare_quick_sort);
    }

    void random_hoare (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::random_hoare_quick_sort);
    }

    void hoare_with_median_of_three (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::hoare_quick_sort_with_median_of_three);
    }

    void lomuto (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::lomuto_quick_sort);
    }
};


class STDSort: public Sort
{
public:
    STDSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    STDSort(
        arr_element *your_space,
        const int space_size,
        const char *file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        try {
            prepare(input_arr, len);
        } catch (...) {
            throw ;
        }

        begin_clock();
        std::sort(arr, arr + len);
        end_clock();
    }
};
# endif
