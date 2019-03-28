
# ifndef SORT_H
# define SORT_H

#include "collect.h"
#include "tools.h"
#include "sorts.h"
#include <iostream>
#include <algorithm>


class Sort
{
protected:
    stop_watch self_watch;
    arr_element *arr;
    FileHandle self_file;

    void prepare (arr_element const input_arr[], const int len)
    {
        if (len > TEST_SIZE) {
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
        # endif
    }
public:

    Sort ()
    {
        arr = test_space;
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

    void open(const char* file_path)
    {

    }
};


class InsertionSort: public Sort
{
public:
    InsertionSort(): Sort() {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_insertion_sort);
    }
};


class MergeSort: public Sort
{
private:
public:
    MergeSort (): Sort () {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_merge_sort);
    }
};


class QuickSort: public Sort
{
public:
    QuickSort (): Sort () {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_quick_sort);
    }
};


class STDSort: public Sort
{
public:
    STDSort (): Sort ()
    {
        #ifdef DEBUG
        arr = std_space;
        #else
        arr = test_space;
        #endif
    }

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
