#ifndef _NULL_MATRIX_HPP_
#define _NULL_MATRIX_HPP_

#include "baseSquareMatrix.hpp"
#include "matrixForwardDecl.hpp"

namespace Core::Maths
{
    template<typename ELEM_TYPE>
    class Matrix<0lu, 0lu, ELEM_TYPE> : public BaseSquareMatrix<Matrix<0lu, 0lu, ELEM_TYPE>, 0lu, ELEM_TYPE>
    {
    public:
        using isNull = std::true_type;
    };
}

#endif 