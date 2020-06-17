#ifndef _MATRIX_FORWARD_DECL_HPP_
#define _MATRIX_FORWARD_DECL_HPP_

#include <cstddef>

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix;

    template<typename ELEM_TYPE>
    class Matrix<1lu, 1lu, ELEM_TYPE>; // Matrix1x1

    template<typename ELEM_TYPE>
    class Matrix<0lu, 0lu, ELEM_TYPE>; // NullMatrix

    template<size_t SIZE, typename ELEM_TYPE>
    class Matrix<SIZE, SIZE, ELEM_TYPE>; // SquareMatrix

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 2lu, ELEM_TYPE>; // Vec2

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 3lu, ELEM_TYPE>; // Vec3

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 4lu, ELEM_TYPE>; // Vec4
}

#endif 