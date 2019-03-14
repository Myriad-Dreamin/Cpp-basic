#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cassert>
using std::max;
int MaxSubsequenceSum(const int A[], const int N)
{
    int ThisSum, MaxSum = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = i; j < N; j++)
        {
            ThisSum = 0;
            for(int k = i; k <= j; k++)
            {
                ThisSum += A[k];
            }
            if(ThisSum > MaxSum)
            {
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}

int MaxSubsequenceSum2(const int A[], const int N)
{
    int ThisSum, MaxSum = 0;
    for(int i = 0; i < N; i++)
    {
        ThisSum = 0;
        for(int j = i; j < N; j++)
        {
            ThisSum += A[j];
            if(ThisSum > MaxSum)
            {
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}

int MaxSubsequenceSum3(const int A[], const int N)
{
    int ThisSum = 0, MaxSum = 0;
    for(int i = 0; i < N; i++)
    {
        ThisSum += A[i];
        if(ThisSum > MaxSum)
        {
            MaxSum = ThisSum;
        }
        else if(ThisSum < 0)
        {
            ThisSum = 0;
        }
    }
    return MaxSum;
}
int A[20005];
int input()
{
    int n;
    scanf("%d",&n);
    return n;
}
int main(){
    clock_t nbeg1 = 0, nbeg2 = 0, nbeg3 = 0;
    const int n = 1, m = 10000;
    srand(time(nullptr));
    for(int repeat_t = 0; repeat_t < n; repeat_t++)
    {
        for(int i = 0; i < m; i++)
        {
            A[i] = rand() - rand();
        }
        clock_t beg = clock();
        int result = MaxSubsequenceSum(A, m);
        nbeg1 += clock() - beg;
        clock_t beg2 = clock();
        int result2 = MaxSubsequenceSum2(A, m);
        nbeg2 += clock() - beg2;
        clock_t beg3 = clock();
        int result3 = MaxSubsequenceSum3(A, m);
        nbeg3 += clock() - beg3;

        assert(result == result2 && result2 == result3);
    }
    printf("testResult:[%.6lf ms, %.6lf ms, %.6lf ms]\n", (double)nbeg1/n, (double)nbeg2/n, (double)nbeg3/n);
}

/*
m = 10
0.000535 ms
0.000223 ms
m = 20
0.003194 ms
0.000686 ms
m = 30
0.010706 ms
0.001403 ms
m = 40
0.025170 ms
0.002313 ms
m = 50
0.049033 ms
0.003347 ms
m = 60
0.085801 ms
0.004718 ms
m = 70
0.138714 ms
0.006394 ms
m = 80
0.206921 ms
0.008501 ms
m = 90
0.292292 ms
0.010801 ms
m = 100
0.398398 ms
0.012501 ms
m = 120
0.695696 ms
0.017602 ms
m = 140
1.105105 ms
0.023102 ms
m = 160
1.645646 ms
0.031103 ms
m = 180
2.336336 ms
0.038104 ms
m = 200
3.193193 ms
0.046705 ms
m = 240
5.481013 ms
m = 280
8.708861 ms
0.091009 ms
m = 320
12.936709 ms
m = 360
18.354430 ms
0.150115 ms
m = 400
25.088608 ms
m = 480
43.202532 ms
0.263226 ms
m = 560
68.367089 ms
m = 640
101.824561 ms
0.466466 ms
m = 720
144.972973 ms
m = 800
198.081081 ms
0.736737 ms
m = 880
263.176471 ms
m = 960
341.882353 ms
m = 1040
434.000000 ms
m = 1120
541.545455 ms
m = 1200
665.727273 ms
0.001659 s
m = 1400
1.058 s
m = 1600
1.576 s
m = 1800
2.241 s
m = 2000
3.079 s
0.004516 s
m = 3000
10.349 s
0.010176 s
m = 4000
24.519 s
0.018121 s
m = 5000
47.920 s
0.028264 s

m = 6000
0.040889 s
m = 7000
0.055444 s
m = 8000
0.072333 s
m = 9000
0.091889 s
m = 10000
0.113333 s
m = 12000
0.163778 s
m = 14000
0.222889 s
m = 16000
0.292000 s
m = 18000
0.369556 s
m = 20000
0.456667 s
m = 24000
0.660 s
m = 28000
0.894 s
m = 32000
1.169 s
m = 36000
1.478 s
m = 40000
1.837 s
m = 48000
2.638 s
m = 56000
3.573 s
m = 64000
4.686 s
m = 72000
5.934 s
m = 80000
7.326 s
m = 96000
10.539 s
m = 108000
13.315 s
m = 120000
16.419 s
m = 140000
22.408 s
m = 160000
29.316 s
m = 180000
36.987 s
m = 200000
45.667 s
*/