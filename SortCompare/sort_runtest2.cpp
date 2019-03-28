
# define DONOTPRINT
# define DEBUG

#include <iostream>

#include "collect.h"
#include "tools.h"
#include "generate.h"
#include "sort_test.h"


using std::cout;
using std::endl;


STDSort std_sort(std_space, TEST_SIZE, "./std_sort.csv");
QuickSort lom_sort(test_space, TEST_SIZE, "./lomuto_quick_sort.csv");
QuickSort hoa_sort(test_space, TEST_SIZE, "./hoare_quick_sort.csv");

QuickSort hoa_sort_rand(test_space, TEST_SIZE, "./random_hoare_quick_sort.csv");
QuickSort hoa_sort_wmt(
    test_space,
    TEST_SIZE,
    "./hoare_quick_sort_with_median_of_three.csv"
);

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

    lom_sort.lomuto(generate_space, len);

    hoa_sort.hoare(generate_space, len);

    hoa_sort_rand.random_hoare(generate_space, len);

    hoa_sort_wmt.hoare_with_median_of_three(generate_space, len);

    switch (ot_mode) {
        case output_mode::to_console: {
            cout << "lomuto quicksort: ";
            lom_sort.show();
            cout << "hoare quicksort: ";
            hoa_sort.show();
            cout << "random hoare quicksort: ";
            hoa_sort_rand.show();
            cout << "hoare quicksort with median of three: ";
            hoa_sort_wmt.show();
            break ;
        }
        case output_mode::to_file: {

            hoa_sort.block(len);
            hoa_sort.block(hoa_sort.used_time());
            hoa_sort.block("mus");
            hoa_sort.block(test_info);
            hoa_sort.newline();

            lom_sort.block(len);
            lom_sort.block(lom_sort.used_time());
            lom_sort.block("mus");
            lom_sort.block(test_info);
            lom_sort.newline();

            hoa_sort_wmt.block(len);
            hoa_sort_wmt.block(hoa_sort_wmt.used_time());
            hoa_sort_wmt.block("mus");
            hoa_sort_wmt.block(test_info);
            hoa_sort_wmt.newline();

            hoa_sort_rand.block(len);
            hoa_sort_rand.block(hoa_sort_rand.used_time());
            hoa_sort_rand.block("mus");
            hoa_sort_rand.block(test_info);
            hoa_sort_rand.newline();

            std_sort.block(len);
            std_sort.block(std_sort.used_time());
            std_sort.block("mus");
            std_sort.block(test_info);
            std_sort.newline();

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
    hoa_sort.settle_clock();
    lom_sort.settle_clock();
    hoa_sort_wmt.settle_clock();
    hoa_sort_rand.settle_clock();
    std_sort.settle_clock();
}

void close_all()
{
    hoa_sort.close();
    lom_sort.close();
    hoa_sort_wmt.close();
    hoa_sort_rand.close();
    std_sort.close();
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