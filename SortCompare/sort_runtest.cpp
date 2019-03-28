
# define DEBUG

#include "collect.h"
#include "tools.h"
#include "generate.h"
#include "sort_test.h"

InsertionSort ins_sort;
MergeSort mer_sort;
QuickSort quc_sort;
STDSort std_sort;
Generate gen(TEST_SIZE, random_seed);

void test_sorts(const int len)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    # ifdef DEBUG
    print_arr(generate_space, len);
    std_sort.primitive(generate_space, len);
    # endif
    
    ins_sort.primitive(generate_space, len);
    ins_sort.show();
    # ifdef DEBUG
    assert_equal(test_space, std_space, len);
    # endif
    
    mer_sort.primitive(generate_space, len);
    mer_sort.show();
    # ifdef DEBUG
    assert_equal(test_space, std_space, len);
    # endif
    
    quc_sort.primitive(generate_space, len);
    quc_sort.show();
    # ifdef DEBUG
    assert_equal(test_space, std_space, len);
    # endif
}

int main()
{
    int test_len = 10;
    gen.random_init(generate_space, test_len);
    test_sorts(test_len);

    gen.special_test(generate_space, test_len);
    test_sorts(test_len);

    gen.special_test2(generate_space, test_len);
    test_sorts(test_len);
    return 0;
}