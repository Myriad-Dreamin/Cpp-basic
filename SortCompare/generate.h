
# ifndef GENERATE_SORT_DATA
# define GENERATE_SORT_DATA

# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif

#include <iostream>
#include <stdexcept>

#include <random>
#include <ctime>


class Generate
{
protected:
    int protect_size;
    unsigned long long random_seed;
public:
    Generate (const int test_size, unsigned long long your_seed=0)
    {
        protect_size = test_size;
        random_seed = your_seed;
    }

    void random_init(arr_element load_arr[], const int len)
    {  
        static std::mt19937 mt_rand(random_seed);
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = mt_rand();
        }
    }

    void special_test(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = 1;
        }
    }

    void special_test2(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = i;
        }
    }

    void special_test3(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = len - i;
        }
    }
};

# endif