#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>
using std::max;
int MaxSubsequenceSum(const int A[], const int N)
{
    int ThisSum, MaxSum = 0;// 1
    for(int i = 0; i < N; i++)// 0 ~ n-1
    {
        for(int j = i; j < N; j++)// i ~ n-1
        {
            ThisSum = 0;// 1
            for(int k = i; k <= j; k++)// i ~ j
            {
                ThisSum += A[k];// 1
            }
            if(ThisSum > MaxSum)// 1
            {
                MaxSum = ThisSum;// 1
            }
        }
    }
    return MaxSum;
}

int MaxSubsequenceSum2(const int A[], const int N)
{
    int ThisSum, MaxSum = 0;// 1
    for(int i = 0; i < N; i++)// 0 ~ n-1
    {
        ThisSum = 0;// 1
        for(int j = i; j < N; j++)// i ~ n-1
        {
            ThisSum += A[j];// 1
            if(ThisSum > MaxSum)// 1
            {
                MaxSum = ThisSum;// 1
            }
        }
    }
    return MaxSum;
}

int MaxSubsequenceSum3(const int A[], const int N)
{
    int ThisSum = 0, MaxSum = 0;// 2
    for(int i = 0; i < N; i++)// 0 ~ n-1
    {
        ThisSum += A[i];// 1
        if(ThisSum > MaxSum)// A1
        {
            MaxSum = ThisSum;// A2
        }
        else if(ThisSum < 0)// A2
        {
            ThisSum = 0;// A3
        }
    }
    return MaxSum;
}
int A[200000005];
int input()
{
    int n;
    std::cin >> n;
    return n;
}
int main(){
    std::ios::sync_with_stdio(false);
    clock_t nbeg1 = 0, nbeg2 = 0, nbeg3 = 0;
    std::cout << "input test_scale(<=2*10^8) and test_vector(a*4 + b*2 + c*1), where a,b,c is the boolean of test_function_switch\n";
    const int n = 1, m = input(), testVector = input();
    srand(time(nullptr));
    for(int repeat_t = 0; repeat_t < n; repeat_t++)
    {
        for(int i = 0; i < m; i++)
        {
            A[i] = rand() - rand();
        }
        clock_t beg = clock();
        int result = (testVector & 4) ? MaxSubsequenceSum(A, m) : -1;
        nbeg1 += clock() - beg;
        clock_t beg2 = clock();
        int result2 = (testVector & 2) ? MaxSubsequenceSum2(A, m) : -1;
        nbeg2 += clock() - beg2;
        clock_t beg3 = clock();
        int result3 = (testVector & 1) ? MaxSubsequenceSum3(A, m) : -1;
        nbeg3 += clock() - beg3;

        // assert(result == result2 && result2 == result3);
    }
    std::cout << "testResult:[" << (double)nbeg1/n <<" ms, "
                                << (double)nbeg2/n <<" ms, "
                                << (double)nbeg3/n <<" ms]" << std::endl;
    std::system("pause");
}

/*
200000000 1
testResult:[0.000000 ms, 0.000000 ms, 450.000000 ms]
*/