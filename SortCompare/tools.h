

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
        return ;
    }

    void stop ()
    {
        LARGE_INTEGER watch_end_time;
        QueryPerformanceCounter(&watch_end_time);
        elapsed += (watch_end_time.QuadPart - watch_begin_time.QuadPart) * 1000000.0 / cpu_frequency.QuadPart;
        return ;
    }

    void restart()
    {
        elapsed = 0;
        start();
        return ;
    }

    void clear()
    {
        elapsed = 0;
        return ;
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

class CsvHandle: public std::fstream
{
private:
    std::ios_base::openmode handle_flag;
    bool opened,newlined;
public:
    CsvHandle ()
    {
        opened = false;
        newlined = false;
    }
    CsvHandle (
        const char *file_path,
        const std::ios_base::openmode open_flag = std::ios::out | std::ios::app
    ): std::fstream(file_path, open_flag)
    {
        opened = true;
        newlined = false;
        handle_flag = open_flag;
    }

    void open (
        const char *file_path,
        const std::ios_base::openmode open_flag = std::ios::out | std::ios::app
    )
    {
        if (opened) {
            std::fstream::close();
        }
        newlined = false;
        *this = CsvHandle(file_path, open_flag);
        return ;
    }
    void close ()
    {
        if (opened) {
            std::fstream::close();
        }
        newlined = false;
        opened = false;
        return ;
    }
    void newline ()
    {
        if (!opened) {
            throw std::domain_error("no file opened");
        }
        newlined = false;
        *this << std::endl;
        return ;
    }

    template<typename T>
    void block(const T &out_element)
    {
        if (!opened) {
            throw std::domain_error("no file opened");
        }
        if (newlined) {
            *this << ",";
        } else {
            newlined = true;
        }
        *this << out_element;
        return ;
    }
};


void print_arr(arr_element const load_arr[], const int len)
{
    # ifndef DONOTPRINT
    for (int i = 0; i < len; i++){
        std::cout << load_arr[i] << " ";
    }
    std::cout << std::endl;
    # endif
    return ;
}

void assert_equal(arr_element const left_arr[], arr_element const right_arr[], const int len)
{
    for (int i = 0; i < len; i++)
    {
        assert(left_arr[i] == right_arr[i]);
    }
    return ;
}


# endif