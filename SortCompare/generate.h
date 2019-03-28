
# ifndef GENERATE_SORT_DATA
# define GENERATE_SORT_DATA

#include "collect.h"

#include <iostream>
#include <stdexcept>

#include <random>
#include <ctime>

void random_init(arr_element load_arr[], const int len)
{  
    static std::mt19937 mt_rand(random_seed);
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    for (int i = 0; i < len; i++) {
        load_arr[i] = mt_rand();
    }
}

void special_test(arr_element load_arr[], const int len)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    for (int i = 0; i < len; i++) {
        load_arr[i] = 1;
    }
}

void special_test2(arr_element load_arr[], const int len)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    for (int i = 0; i < len; i++) {
        load_arr[i] = i;
    }
}

# endif