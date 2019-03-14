#include <iostream>
#include <algorithm>
#include "Matrix.h"

namespace MatrixSpace
{
    template <typename MT>
    inline std::ostream& operator<< (std::ostream &out_s, Matrix <MT> const &out_mat)
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

    template <typename MT>
    Matrix<MT>::Matrix ()
    {
        aloc_array = nullptr;
        row = col = 0;
    }

    template <typename MT>
    Matrix<MT>::Matrix (int const size_row, int const size_col)
    {
        rmc = size_row * size_col;
        aloc_array = new int[rmc];
        row = size_row;
        col = size_col;
    }

    template <typename MT>
    Matrix<MT>::~Matrix ()
    {
        if(aloc_array != nullptr)delete[] aloc_array;
        aloc_array = nullptr;
        rmc = row = col = 0;
    }

    template <typename MT>

    inline MT* Matrix<MT>::operator[] (int const sel_row) const
    {
        return aloc_array + sel_row * col;
    }

    template <typename MT>
    Matrix <MT>* Matrix<MT>::operator+ (Matrix <MT> const &right_mat) const
    {
        Matrix <MT> *res_mat = new Matrix <MT>(row, col);
        for (int i = 0; i < rmc; i++)
        {
            res_mat->aloc_array[i] = aloc_array[i] + right_mat.aloc_array[i];
        }
        return res_mat;
    }

    template <typename MT>
    Matrix <MT>* Matrix<MT>::operator- (Matrix <MT> const &right_mat) const
    {
        Matrix <MT> *res_mat = new Matrix <MT>(row, col);
        for (int i = 0; i < rmc; i++)
        {
            res_mat->aloc_array[i] = aloc_array[i] - right_mat.aloc_array[i];
        }
        return res_mat;
    }

    template <typename MT>
    void Matrix<MT>::initfs ()
    {
        using std::cin;

        for (int i = 0; i < rmc; i++)
        {
            cin >> aloc_array[i];
        }
        return ;
    }
}
