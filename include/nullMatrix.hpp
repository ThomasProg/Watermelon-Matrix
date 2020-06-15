#ifndef _MATRIX1X1_HPP_
#define _MATRIX1X1_HPP_

#include "baseSquareMatrix.hpp"

namespace Core::Maths
{
    template<typename ELEM_TYPE>
    class Matrix<1lu, 1lu, ELEM_TYPE> : public BaseSquareMatrix<Matrix<1lu, 1lu, ELEM_TYPE>, 1lu, ELEM_TYPE>
    {
    public:
        using isNull = std::true_type;
    };

    template<typename ELEM_TYPE>
    using NullMatrix = Matrix<0lu, 0lu, ELEM_TYPE>;
}

#endif 