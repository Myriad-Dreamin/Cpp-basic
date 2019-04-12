
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

namespace MatrixSpace
{
    /*
     * 当Matrix运行中发生异常/错误时，抛出该Exception
     * 使用MatrixError("Exception Descript...")产生一个Exception
     * 必须传入异常说明，不允许无参构造
     */
    class MatrixError
    {
    protected:

        // err_desc: 错误信息的描述
        std::string err_desc;

    public:

        /*
         * 构造函数
         * @str: 常量字符串
         *
         * 传入一个常量字符串初始化MatrixError
         */
        MatrixError (const char *str);

        /*
         * 构造函数
         * @str: 常量字符串
         *
         * 传入一个常量字符串初始化MatrixError
         */
        MatrixError (std::string &str);

        /*
         * 拷贝构造函数
         * @mat_err: 其他MatrixError
         *
         * 传入一个常量字符串初始化MatrixError
         */
        MatrixError (const MatrixError &mat_err);

        /*
         * @ret: 返回一个字符串，为MatrixError的描述
         */
        const char *what() const;
    };

    /*
     * 当Matrix二元运算不匹配时，发生该Exception
     * 使用MatrixCalculateError("Exception Descript...")产生一个Exception
     */
    typedef MatrixError MatrixCalculateError;

    /*
     * 当访问超过了Matrix的行大小时，发生此错误
     * 使用MatrixCalculateError("Exception Descript...")产生一个Exception
     */
    typedef MatrixError MatrixReferenceError;

    /*
     * 一个泛型的矩阵类，支持加减运算
     * 如果你定义了预编译宏 SAFEMATRIX 类会帮你检查可能的错误，否则它会相信你的所有举止都是聪明的。
     *
     * Unsafe Matrix:
     * 注意数组的初始化采用了new，确保你的new和delete配对使用
     * 注意数组的加减运算采用了new，请不要使用链运算，这会导致内存泄漏
     *
     * Safe Matrix:
     * 防止数组访问越界
     */
    template <typename MatrixType>
    class Matrix
    {
    private:

        int row, col, rmc;

        MatrixType *aloc_array;

        template <typename MtxType>
        friend std::ostream &operator<< (std::ostream &os, Matrix<MtxType> const &out_mat);

    public:
        /*
         * 默认构造函数
         *
         * 此时，矩阵的行列值均为0,数组指针为nullptr
         */
        Matrix ();

        Matrix (const Matrix<MatrixType> &right_mat);

        /*
         * 带有行列输入的构造函数
         * @size_row: 行的大小
         * @size_col: 列的大小
         *
         * 此时，矩阵的行列值为(size_row, size_col)
         * 数组恰好支持[0 ~ (size_row - 1)][0 ~ (size_col - 1)]的访问
         * ...
         */
        Matrix (int const size_row, int const size_col);

        /*
         * 矩阵的析构函数
         *
         * 会废弃所有已申请的内存
         */
        ~Matrix ();

        /*
         * []符号重载
         *
         * 假设你的矩阵实例是Mat，使用Mat[x][y]访问第x行第y列的元素
         * x在0 ~ (size_row - 1)之间，y在0 ~ (size_col - 1)之间
         */
        inline MatrixType *operator[] (int const sel_row) const;

        /*
         * +符号重载
         * @arg1: Matrix<MatrixType>
         * @arg2: Matrix<MatrixType>
         * @res: Matrix<MatrixType>*
         *
         * 假设你的矩阵实例是A, B，使用一个指针接受运算结果C = A + B
         * 使用delete C，结束输出结果的生命周期
         * 要求A和B的行列大小相同
         */
        Matrix<MatrixType> *operator+ (Matrix<MatrixType> const &right_mat) const;

        /*
         * -符号重载
         * @arg1: Matrix<MatrixType>
         * @arg2: Matrix<MatrixType>
         * @res: Matrix<MatrixType>*
         *
         * 假设你的矩阵实例是A, B，使用一个指针接受运算结果C = A - B
         * 使用delete C，结束输出结果的生命周期
         * 要求A和B的行列大小相同
         */
        Matrix<MatrixType> *operator- (Matrix<MatrixType> const &right_mat) const;

        /*
         * =符号重载
         * @arg1: Matrix<MatrixType>
         *
         * 完成赋值的逻辑检查
         */
        const Matrix<MatrixType> operator= (Matrix<MatrixType> const &right_mat);

        /*
         * initfs
         *
         * 根据矩阵初始化的row和col依行列顺序读入MatrixType类型的元素.
         */
        void initfs ();
    };
}

#endif
