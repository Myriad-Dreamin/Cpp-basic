

# ifndef TOOLS_H
# define TOOLS_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


#include <iostream>
#include <stdexcept>
#include <bitset>
#include <ctime>
#include <windows.h>
#include <direct.h>		//for mkdir rmdir
#include <io.h>			//for access

#include <cassert>
#include <fstream>

// in Win32 access = _access, mkdir = _mkdir, rm = _rmdir
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#define RMDIR(a) _rmdir((a))

// ?*"<>/;
enum escape_char_lo: unsigned long long
{
    double_quotes = 1ULL << 34,
    asterisk = 1ULL << 42,
    slash = 1ULL << 47,
    semicon = 1ULL << 59,
    less_than = 1ULL << 60,
    greater_than = 1ULL << 62,
    question_mark = 1ULL << 63
};
// \|
enum escape_char_hi: unsigned long long
{
    backslash = 1ULL << (92 - 64),
    vertical_bar = 1ULL << (124 - 64),
};

// do not use -128 ~ -1 as key.
const std::bitset<128> escape_char_maps_lo(
    escape_char_lo::double_quotes ||
    escape_char_lo::asterisk ||
    escape_char_lo::slash ||
    escape_char_lo::semicon ||
    escape_char_lo::less_than ||
    escape_char_lo::greater_than ||
    escape_char_lo::question_mark
);
const std::bitset<128> escape_char_maps_hi(
    escape_char_hi::backslash ||
    escape_char_hi::vertical_bar
);
const std::bitset<128> escape_char_maps = (escape_char_maps_hi << 64) | escape_char_maps_lo;

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

class FileHandle: public std::fstream
{
private:
    std::ios_base::openmode handle_flag;
    bool opened,newlined;
public:
    FileHandle ()
    {
        opened = false;
        newlined = false;
    }
    FileHandle (
        const std::string& file_path,
        const std::ios_base::openmode open_flag = std::ios::out | std::ios::app
    ): std::fstream(file_path, open_flag)
    {
        opened = std::fstream::is_open();
        newlined = false;
        handle_flag = open_flag;
    }

    void open (
        const std::string& file_path,
        const std::ios_base::openmode open_flag = std::ios::out | std::ios::app
    )
    {
        if (opened) {
            std::fstream::close();
        }
        std::fstream::open(file_path, open_flag);
        opened = std::fstream::is_open();
        newlined = false;
        handle_flag = open_flag;
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

    bool opening ()
    {
        return opened;
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

    template<typename T>
    void output(const T &out_element)
    {
        if (!opened) {
            throw std::domain_error("no file opened");
        }
        if (newlined) {
            *this << " ";
        } else {
            newlined = true;
        }
        *this << out_element;
        return ;
    }

    bool get(int &in_element)
    {
        if (!opened) {
            throw std::domain_error("no file opened");
        }
        if (this->eof()) {
            return false;
        }
        *this >> in_element;
        return true;
    }
};


class DataSet
{
protected:
    std::string self_path;
    std::string self_name;
    std::string self_file_prefix;
    FileHandle self_handle;
    int case_count;
    bool make_dir(const std::string& strPath)
    {
        int i = 0;
        int nDirLen = strPath.length();
        if (nDirLen <= 0)
            return false;
        char *pDirTemp = new char[nDirLen + 4];
        strPath.copy(pDirTemp, nDirLen + 1, 0);// +1 to copy '\0'
        pDirTemp[nDirLen] = '\0';
        
        if (pDirTemp[nDirLen - 1] != '\\' && pDirTemp[nDirLen - 1] != '/')
        {
            pDirTemp[nDirLen] = '/';
            pDirTemp[nDirLen + 1] = '\0';
            nDirLen++;
        }
        
        for (i = 0; i < nDirLen; i++)
        {
            if (pDirTemp[i] == '\\' || pDirTemp[i] == '/')
            {
                pDirTemp[i] = '\0';

                int statu;
                statu = ACCESS(pDirTemp, 0);
                if (statu != 0)
                {
                    statu = MKDIR(pDirTemp);
                    if (statu != 0)
                    {
                        return false;
                    }
                }
                pDirTemp[i] = '/';
            }
        }
        delete[] pDirTemp;
        return true;
    }

    bool remove_dir(const std::string & path)
    {
        std::string strPath = path;
        struct _finddata_t fb;   

        if (strPath.at(strPath.length() - 1) != '\\' || strPath.at(strPath.length() - 1) != '/') {
            strPath.append("\\");
        }
        std::string findPath = strPath + "*";
        intptr_t handle;
        handle = _findfirst(findPath.c_str(), &fb);
        
        if (handle != -1L)
        {
            std::string pathTemp;
            do
            {
                
                if (strcmp(fb.name, "..")!=0 && strcmp(fb.name, ".")!=0)
                {
                    pathTemp.clear();
                    pathTemp = strPath + std::string(fb.name);
                    if (fb.attrib == _A_SUBDIR)
                    {
                        remove_dir(pathTemp.c_str());
                    } 
                    else
                    {
                        remove(pathTemp.c_str());
                    }
                }
            } while (0 == _findnext(handle, &fb));
            _findclose(handle);
        }
        return !RMDIR(strPath.c_str());
    }

public:
    DataSet(const std::string &fold_path, const std::string &dataset_name)
    {
        set_path(fold_path);
        set_name(dataset_name);
        self_file_prefix = self_path + self_name;
        case_count = 0;
    }

    bool set_path(const std::string &fold_path)
    {
        if (fold_path.length() > 255) {
            return false;
        }
        for (auto character : fold_path) {
            if (character < 0) {
                return false;
            }
            if (character == '\\' || character == '/') {
                continue;
            }
            if (escape_char_maps[character]) {
                return false;
            }
        }
        self_path = fold_path;
        if ((self_path.back() != '\\') && (self_path.back() != '/')) {
            if (self_path.length() == 255) {
                return false;
            }
            self_path.push_back('/');
        }
        self_file_prefix = self_path + self_name;
        return true;
    }

    bool set_name(const std::string &dataset_name)
    {
        if (dataset_name.length() > 255) {
            return false;
        }
        for (auto character : dataset_name) {
            if (character < 0) {
                return false;
            }
            if (escape_char_maps[character]) {
                return false;
            }
        }
        self_name = dataset_name;
        self_file_prefix = self_path + self_name;
        return true;
    }

    bool build_set()
    {
        return make_dir(self_path);
    }

    bool clear_set()
    {
        std::cout << "warning! this operation will remove folds and files recursively" << std::endl;
        
        std::string get_answer;
        reanswer:
        std::cout << "continue?(Y/n)" << std::endl;
        std::cin >> get_answer;
        if (get_answer.length() != 1) {
            std::cout << "output Yy or Nn" << std::endl;
            goto reanswer;
        }

        switch(get_answer[0]) {
            case 'Y':case 'y': {
                case_count=0;
                return remove_dir(self_path);
            }
            case 'N':case 'n': {
                return false;
            }
            default : {
                std::cout << "output Yy or Nn" << std::endl;
                goto reanswer;
            }
        }
    }

    bool force_clear_set()
    {
        case_count=0;
        return remove_dir(self_path);
    }

    void new_testcase()
    {
        self_handle.open(
            self_file_prefix + std::to_string(++case_count) + ".txt",
            std::ios::ate | std::ios::out
        );
        if (!self_handle.opening()) {
            throw std::domain_error(
                "can't create " +
                self_file_prefix +
                std::to_string(++case_count) +
                ".txt"
            );
        }
    }

    void open_testcase(const int idx)
    {
        self_handle.open(self_file_prefix + std::to_string(idx) + ".txt", std::ios::ate | std::ios::out);
        if (!self_handle.opening()) {
            throw std::domain_error("can't open " + self_file_prefix + std::to_string(idx) + ".txt");
        }
    }

    void close_testcase()
    {
        self_handle.close();
    }

    int size()
    {
        return case_count;
    }

    virtual void dump_info()
    {
        self_handle.open(self_file_prefix + "_info.txt", std::ios::ate | std::ios::out);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + "_info.txt is not opening");
        }
        self_handle << case_count << std::endl;
        self_handle.close();
    }

    virtual void load_info()
    {
        self_handle.open(self_file_prefix + "_info.txt", std::ios::in);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + "_info.txt is not opening");
        }
        self_handle >> case_count;
        self_handle.close();
    }

};


class IntSet: public DataSet
{
protected:

    int max_int_count;
public:

    IntSet(const std::string &fold_path, const std::string &dataset_name) :
        DataSet(fold_path, dataset_name)
    {
        max_int_count = 0;
    }

    virtual void dump_info()
    {
        self_handle.open(self_file_prefix + "_info.txt", std::ios::ate | std::ios::out);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + "_info.txt is not opening");
        }
        self_handle << case_count << std::endl;
        self_handle << max_int_count << std::endl;
        self_handle.close();
    }

    virtual void load_info()
    {
        self_handle.open(self_file_prefix + "_info.txt", std::ios::in);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + "_info.txt is not opening");
        }
        self_handle >> case_count;
        self_handle >> max_int_count;
        self_handle.close();
    }

    void batch_ints(const int batch_space[],const int len)
    {
        for (int i = 0; i < len; i++) {
            self_handle.output(batch_space[i]);
        }
        max_int_count = std::max(max_int_count, len);
    }

    void load_testcase_ints(int *dump_space, int idx)
    {
        self_handle.open(self_file_prefix + std::to_string(idx) + ".txt", std::ios::in);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + std::to_string(idx) + ".txt is not opening");
        }
        while(self_handle.get(*dump_space))dump_space++;
        self_handle.close();
    }

    int possible_space_size()
    {
        return max_int_count;
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

unsigned int rand_uint()
{
    static unsigned int seed = time(nullptr);
    return seed = ((seed * 23333) ^ 19991213);
}


# endif