
// # define DONOTPRINT
# define DEBUG

#include <iostream>

#include "collect.h"
#include "tools.h"
#include "generate.h"
#include "sort_test.h"


using std::cout;
using std::endl;

InsertionSort ins_sort(test_space, TEST_SIZE, "./insertion_sort.csv");
MergeSort mer_sort(test_space, TEST_SIZE, "./merge_sort.csv");
QuickSort quc_sort(test_space, TEST_SIZE, "./hoare_quick_sort.csv");
STDSort std_sort(std_space, TEST_SIZE, "./std_sort.csv");

Generate gen(TEST_SIZE, random_seed);


enum output_mode {to_console, to_file, do_nothing};
void test_sorts(
    const int len,
    const output_mode ot_mode = output_mode::do_nothing,
    const char * test_info=""
)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    # ifdef DEBUG
    print_arr(generate_space, len);
    std_sort.primitive(generate_space, len);
    # endif

    ins_sort.primitive(generate_space, len);

    mer_sort.primitive(generate_space, len);

    quc_sort.primitive(generate_space, len);

    switch (ot_mode) {
        case output_mode::to_console: {
            cout << "insertion sort: ";
            ins_sort.show();
            cout << "merge sort: ";
            mer_sort.show();
            cout << "quick sort: ";
            quc_sort.show();
            break ;
        }
        case output_mode::to_file: {

            ins_sort.block(len);
            ins_sort.block(ins_sort.used_time());
            ins_sort.block("mus");
            ins_sort.block(test_info);
            ins_sort.newline();

            mer_sort.block(len);
            mer_sort.block(mer_sort.used_time());
            mer_sort.block("mus");
            mer_sort.block(test_info);
            mer_sort.newline();

            quc_sort.block(len);
            quc_sort.block(quc_sort.used_time());
            quc_sort.block("mus");
            quc_sort.block(test_info);
            quc_sort.newline();

            break ;
        }
        default: {
            break ;
        }
    }
    return ;
}

void clearclocks()
{
    std_sort.settle_clock();
    ins_sort.settle_clock();
    mer_sort.settle_clock();
    quc_sort.settle_clock();
}

void close_all()
{
    std_sort.close();
    ins_sort.close();
    mer_sort.close();
    quc_sort.close();
}

int main()
{
    int test_len = 3000;
    gen.random_init(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "random_init");
    clearclocks();

    gen.special_test(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "special_test");
    clearclocks();

    gen.special_test2(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "special_test2");
    clearclocks();

    close_all();
    return 0;
}