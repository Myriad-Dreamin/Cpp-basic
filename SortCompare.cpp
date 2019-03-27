
// # define DEBUG

#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif  // _WIND32

using std::swap;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

const int TEST_SIZE = 1000;
typedef int arr_element;
enum time_unit {musec, misec, sec};


auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
arr_element test_space[TEST_SIZE], generate_space[TEST_SIZE];

class stop_watch
{
private:

    LARGE_INTEGER cpu_frequency;
    LARGE_INTEGER watch_begin_time;
    long long elapsed;

public:

    stop_watch () : elapsed(0)
    {
        QueryPerformanceFrequency(&cpu_frequency);
    }

    ~stop_watch () {}
public:

    void start ()
    {
        QueryPerformanceCounter(&watch_begin_time);
    }

    void stop ()
    {
        LARGE_INTEGER watch_end_time;
        QueryPerformanceCounter(&watch_end_time);
        elapsed += (watch_end_time.QuadPart - watch_begin_time.QuadPart) * 1000000.0 / cpu_frequency.QuadPart;
    }

    void restart()
    {
        elapsed = 0;
        start();
    }

    void clear()
    {
        elapsed = 0;
    }

    //microsecond
    double microsec()
    {
        return static_cast<double>(elapsed);
    }
    //millisecond
    double millisec()
    {
        return elapsed / 1000.0;
    }
    //second
    double sec()
    {
        return elapsed / 1000000.0;
    }
};

class Sort
{
protected:
    stop_watch self_watch;
    arr_element *arr;

    void prepare (const arr_element input_arr[], const int len)
    {
        if (len > TEST_SIZE) {
            throw std::invalid_argument("length to copy is out of range");
        }
        memcpy(arr, input_arr, sizeof(arr_element) * len);    
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

    const double show (const time_unit t_unit=time_unit::musec)
    {
        switch(t_unit) {
            case time_unit::musec: {
                return self_watch.microsec();
            }
            case time_unit::misec: {
                return self_watch.millisec();
            }
            case time_unit::sec: {
                return self_watch.sec();
            }
            default: {
                throw std::invalid_argument(
                    "It is impossible reached? Did you input a wrong time_unit to show?"
                );
            }
        }
    }
};

class InsertionSort: public Sort
{
public:
    InsertionSort(): Sort() {}

    void simple(const arr_element input_arr[], const int len)
    {
        int tmp, j;
        try {
            prepare(input_arr, len);
        } catch (...) {
            throw ;
        }
        begin_clock();
        for (int i=1; i<len; i++) {
            tmp = arr[i];
            j = i - 1;
            while (j >= 0 && tmp < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = tmp;
        }
        end_clock();
    }
} ins_sort;

void random_init(arr_element load_arr[], const int len)
{  
    static std::mt19937 mt_rand(random_seed);
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    for (int i=0; i<len; i++){
        load_arr[i] = mt_rand();
    }
}

void print_arr(const arr_element load_arr[], const int len)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    for (int i=0; i<len; i++){
        cout << load_arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    random_init(generate_space, 10);
    print_arr(generate_space, 10);
    return 0;
}