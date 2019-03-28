

# ifndef TOOLS_H
# define TOOLS_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


#include <iostream>
#include <stdexcept>

#include <cassert>
#include <fstream>


#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif  // _WIND32


enum time_unit {musec, misec, sec};
enum iofstream_flag : unsigned char
{
    app_flag       = 1 << 0,
    ate_flag       = 1 << 1,
    binary_flag    = 1 << 2,
    in_flag        = 1 << 3,
    out_flag       = 1 << 4,
    trunc_flag     = 1 << 5
};

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

class FileHandle {
private:
    std::fstream handle;
    unsigned char handle_flag;
    bool opened;
public:
    FileHandle ()
    {
        opened = false;
    }
    void open (
        const char *file_path,
        const unsigned char open_flag = iofstream_flag::out_flag | iofstream_flag::app_flag
    )
    {
        if (opened) {
            handle.close();
        }
        handle.open(file_path,std::ios_base::openmode(open_flag));
        handle_flag = open_flag;
    }
    
    void close()
    {
        if (opened) {
            handle.close();
        }
        handle_flag = 0;
    }
};


void print_arr(arr_element const load_arr[], const int len)
{
    for (int i = 0; i < len; i++){
        std::cout << load_arr[i] << " ";
    }
    std::cout << std::endl;
}

void assert_equal(arr_element const left_arr[], arr_element const right_arr[], const int len)
{
    for (int i = 0; i < len; i++)
    {
        assert(left_arr[i] == right_arr[i]);
    }
}


# endif