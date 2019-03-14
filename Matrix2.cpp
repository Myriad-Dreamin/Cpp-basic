#include <iostream>
#include <algorithm>

template <typename MatrixType>
class Matrix
{
private:

    int row, col, rmc;

    MatrixType *aloc_array;

    template <typename MtxType>
    friend std::ostream &operator<< (std::ostream &os, Matrix <MtxType> const &out_mat);

public:

    Matrix (int const size_row, int const size_col)
    {
        aloc_array = new int[size_row*size_col];
        row = size_row;
        col = size_col;
        rmc = row * col;
    }
    
    ~Matrix ()
    {
        delete[] aloc_array;
        aloc_array = nullptr;
    }

    inline MatrixType *operator[] (int const sel_row) const
    {
        return aloc_array + sel_row * col;
    }
    
    Matrix <MatrixType> *operator+ (Matrix <MatrixType> const &right_mat) const
    {
        Matrix <MatrixType> *res_mat = new Matrix <MatrixType>(row, col);
        for (int i = 0; i < rmc; i++)
        {
            res_mat->aloc_array[i] = aloc_array[i] + right_mat.aloc_array[i];
        }
        return res_mat;
    }

    Matrix <MatrixType> *operator- (Matrix <MatrixType> const &right_mat) const
    {
        Matrix <MatrixType> *res_mat = new Matrix <MatrixType>(row, col);
        for (int i = 0; i < rmc; i++)
        {
            res_mat->aloc_array[i] = aloc_array[i] - right_mat.aloc_array[i];
        }
        return res_mat;
    }

    //init from stream
    void initfs ()
    {
        using std::cin;

        for (int i = 0; i < rmc; i++)
        {
            cin >> aloc_array[i];
        }
        return ;
    }
};

template <typename MatrixType>
inline std::ostream &operator<< (std::ostream &out_s, Matrix <MatrixType> const &out_mat)
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