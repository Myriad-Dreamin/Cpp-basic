
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

namespace MatrixSpace
{

    class MatrixCalculateError
    {
    public:

        MatrixCalculateError () {}

        MatrixCalculateError (const char *str);

        MatrixCalculateError (std::string &str);

        MatrixCalculateError (const MatrixCalculateError &rhs);

        const char* what() const;

    protected:

        std::string msg;
    };

    template <typename MatrixType>
    class Matrix
    {
    private:

        int row, col, rmc;

        MatrixType *aloc_array;

        template <typename MtxType>
        friend std::ostream &operator<< (std::ostream &os, Matrix <MtxType> const &out_mat);

    public:

        Matrix ();

        Matrix (int const size_row, int const size_col);

        ~Matrix ();

        inline MatrixType *operator[] (int const sel_row) const;

        Matrix <MatrixType> *operator+ (Matrix <MatrixType> const &right_mat) const;

        Matrix <MatrixType> *operator- (Matrix <MatrixType> const &right_mat) const;
        //init from stream
        void initfs ();
    };
}

#endif
