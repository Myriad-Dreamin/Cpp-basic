
#include <iostream>
#include "Matrix.h"
/*
 * MatrixError
 *
 * 矩阵Exceptions的实现
 */
namespace MatrixSpace
{
	MatrixError::MatrixError (const char *str)
    {
        err_desc = std::string(str);
    }

    MatrixError::MatrixError (std::string &str)
    {
        err_desc = str;
    }

    MatrixError::MatrixError (const MatrixError &mat_err)
    {
        err_desc = mat_err.err_desc;
    }

    const char *MatrixError::what () const
    {
        return err_desc.c_str();
    }
}
