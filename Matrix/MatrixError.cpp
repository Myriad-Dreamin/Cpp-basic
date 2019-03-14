
#include <iostream>

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

    const char* MatrixCalculateError::what() const
    {
        return msg.c_str();
    }
}
