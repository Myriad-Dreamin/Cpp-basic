#include <iostream>
#include <algorithm>
#include <string>
class MatrixCalculateError
{
public:
    MatrixCalculateError () {}

    MatrixCalculateError (const char str[])
    {
        msg = std::string(str);
    }

    MatrixCalculateError (std::string &str)
    {
        msg = str;
    }

    MatrixCalculateError (MatrixCalculateError& rhs)
    {
        msg = rhs.msg;
    }

    std::string msg;
};

struct Matrix
{
    int row, col, rmc;

    int *aloc_array;

    Matrix()
    {
        row = col = rmc = 0;
        aloc_array = nullptr;
    }

    friend std::ostream &operator<< (std::ostream &os, Matrix const &out_mat);

    //底层实现，默认不捕捉异常
    inline int *operator[] (int const sel_row) const
    {
        return aloc_array + sel_row * col;
    }
};

inline std::ostream &operator<< (std::ostream &out_s, Matrix const &out_mat)
{
    for (int i = 0; i < out_mat.row; i++)
    {
        if (i != 0)out_s << '\n';
        for (int j = 0; j < out_mat.col; j++)
        {
            if ( j != 0)out_s << ' ';
            out_s << out_mat[i][j];
        }
    }
    return out_s;
}

void initMatrix (Matrix &mat, int const size_row, int const size_col)
{
    mat.rmc = size_row * size_col;
    mat.aloc_array = new int[mat.rmc];
    mat.row = size_row;
    mat.col = size_col;
}

void inputMatrix (Matrix &mat)
{
    using std::cin;

    for (int i = 0; i < mat.rmc; i++)
    {
        cin >> mat.aloc_array[i];
    }
    return ;
}

void deleteMatrix (Matrix &mat)
{
    delete[] mat.aloc_array;
    mat.aloc_array = nullptr;
    mat.rmc = mat.row = mat.col = 0;
}

void tryDeleteMatrix(Matrix &mat)
{
    if(mat.aloc_array != nullptr)delete[] mat.aloc_array;
    mat.aloc_array = nullptr;
    mat.rmc = mat.row = mat.col = 0;

}

void addMatrix (Matrix const &mat_left, Matrix const &mat_right, Matrix &mat_res)
{
    if((mat_left.row != mat_right.row) || (mat_left.col != mat_right.col))
    {
        throw "mat_left not equal to mat_right";//MatrixCalculateError("mat_left not equal to mat_right");
    }

    if((mat_res.row != mat_left.row) || (mat_res.col != mat_left.col))
    {
        if(mat_res.aloc_array != nullptr)deleteMatrix(mat_res);
        try {
            initMatrix(mat_res, mat_left.row, mat_left.col);
        }
        catch (std::bad_alloc &e)
        {
            throw e;
        }
    }
    
    for (int i = 0; i < mat_res.rmc; i++)
    {
        mat_res.aloc_array[i] = mat_left.aloc_array[i] + mat_right.aloc_array[i];
    }
}

void subMatrix (Matrix const &mat_left, Matrix const &mat_right, Matrix &mat_res)
{
    if((mat_left.row != mat_right.row) || (mat_left.col != mat_right.col))
    {
        throw "mat_left not equal to mat_right";//MatrixCalculateError("mat_left not equal to mat_right");
    }

    if((mat_res.row != mat_left.row) || (mat_res.col != mat_left.col))
    {
        if(mat_res.aloc_array != nullptr)deleteMatrix(mat_res);
        try {
            initMatrix(mat_res, mat_left.row, mat_left.col);
        }
        catch (std::bad_alloc &e)
        {
            throw e;
        }
    }

    for (int i = 0; i < mat_res.rmc; i++)
    {
        mat_res.aloc_array[i] = mat_left.aloc_array[i] - mat_right.aloc_array[i];
    }
}

int main ()
{
    std::ios::sync_with_stdio (false);
    using std::cout;
    using std::endl;

    Matrix A, B, C;
    
    initMatrix(A, 4, 5);
    initMatrix(B, 4, 5);

    inputMatrix(A);
    inputMatrix(B);
    
    addMatrix(A, B, C);
    cout << "A+B:" << endl << C << endl;

    subMatrix(A, B, C);
    cout << "A-B:" << endl << C << endl;

    tryDeleteMatrix(A);
    tryDeleteMatrix(B);
    tryDeleteMatrix(C);
    
    return 0;
}

/*
0 0 1 0 5
1 2 3 4 2
1 2 2 2 2
3 3 3 3 3

5 4 3 2 1
1 2 3 4 2
3 1 2 4 5
3 1 2 4 5
*/