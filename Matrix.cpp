#include <iostream>
#include <algorithm>
#include <string>

class MatrixCalculateError
{
public:
    MatrixCalculateError () {}

    MatrixCalculateError(char* str)
    {
        msg = str;
    }

    MatrixCalculateError(MatrixCalculateError& const rhs)
    {
        this->msg = rhs.msg;
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

void initMatrix (Matrix *mat, int const size_row, int const size_col)
{
    mat->rmc = size_row * size_col;
    mat->aloc_array = new int[mat->rmc];
    mat->row = size_row;
    mat->col = size_col;
}

void inputMatrix (Matrix *mat)
{
    using std::cin;

    for (int i = 0; i < rmc; i++)
    {
        cin >> mat->aloc_array[i];
    }
    return ;
}

void *deleteMatrix (Matrix *mat)
{
    delete[] mat->aloc_array;
    mat->aloc_array = nullptr;
    mat->rmc = mat->row = mat->col = 0;
}

void addMatrix (Matrix const *mat_left, Matrix const *mat_right, Matrix *mat_res)
{
    if((mat_left->row != mat_right->row) || (mat_left->col != mat_right->col))
    {
        throw MatrixCalculateError("mat_left not equal to mat_right");
    }

    if((mat_res->row != mat_left->row) || (mat_res->col != mat_left->col))
    {
        if(mat_res->aloc_array != nullptr)deleteMatrix(mat_res);
        try {
            initMatrix(mat_res, mat_left->row, mat_left->col);
        }
        
    }
    
    for (int i = 0; i < rmc; i++)
    {
        res_mat->aloc_array[i] = aloc_array[i] + right_mat.aloc_array[i];
    }
    return res_mat;
}

void SubMatrix (Matrix *A, Matrix *B, Matrix *C)
{
    Matrix <MatrixType> *res_mat = new Matrix <MatrixType>(row, col);
    for (int i = 0; i < rmc; i++)
    {
        res_mat->aloc_array[i] = aloc_array[i] - right_mat.aloc_array[i];
    }
    return res_mat;
}

int main ()
{
    std::ios::sync_with_stdio (false);
    using std::cout;
    using std::endl;

    Matrix <int> *A = new Matrix <int> (4, 5);
    Matrix <int> *B = new Matrix <int> (4, 5);

    A->initfs ();

    B->initfs ();

    Matrix <int> *C = (*A) + (*B);
    cout << "A+B:" << endl << *C << endl;
    delete C;

    C = (*A) - (*B);
    cout << "A-B:" << endl << *C << endl;
    delete C;

    delete A;
    delete B;
    
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