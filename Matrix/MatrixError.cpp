
#include <iostream>

/*
 * MatrixError
 *
 * 矩阵Exceptions的实现
 */
namespace MatrixSpace
{
	MatrixCalculateError::MatrixCalculateError (const char *str)
    {
        msg = std::string(str);
    }

    MatrixCalculateError::MatrixCalculateError (std::string &str)
    {
        msg = str;
    }

    MatrixCalculateError::MatrixCalculateError (const MatrixCalculateError &rhs)
    {
        msg = rhs.msg;
    }

    const char *MatrixCalculateError::what () const
    {
        return msg.c_str();
    }
    MatrixReferenceError::MatrixReferenceError (const char *str)
    {
        msg = std::string(str);
    }

    MatrixReferenceError::MatrixReferenceError (std::string &str)
    {
        msg = str;
    }

    MatrixReferenceError::MatrixReferenceError (const MatrixReferenceError &rhs)
    {
        msg = rhs.msg;
    }

    const char *MatrixReferenceError::what () const
    {
        return msg.c_str();
    }
}
