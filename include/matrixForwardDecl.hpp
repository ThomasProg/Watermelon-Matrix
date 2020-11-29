#ifndef _MATRIX_FORWARD_DECL_HPP_
#define _MATRIX_FORWARD_DECL_HPP_

#include <cstddef>

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix;

    // Matrix1x1
    template<typename ELEM_TYPE>
    class Matrix<1lu, 1lu, ELEM_TYPE>; 
    template<typename ELEM_TYPE>
    using Matrix1x1 = Matrix<1lu, 1lu, ELEM_TYPE>;

    // NullMatrix
    template<typename ELEM_TYPE>
    class Matrix<0lu, 0lu, ELEM_TYPE>; 
    template<typename ELEM_TYPE>
    using NullMatrix = Matrix<0lu, 0lu, ELEM_TYPE>;

    // SquareMatrix
    template<size_t SIZE, typename ELEM_TYPE>
    class Matrix<SIZE, SIZE, ELEM_TYPE>; 
    template<size_t SIZE, typename ELEM_TYPE>
    using SquareMatrix = Matrix<SIZE, SIZE, ELEM_TYPE>;

    // // Matrix3x3
    // template<size_t SIZE, typename ELEM_TYPE>
    // using SquareMatrix = Matrix<SIZE, SIZE, ELEM_TYPE>;

    // Vec
    template<size_t SIZE, typename ELEM_TYPE>
    struct Matrix<1lu, SIZE, ELEM_TYPE>;
    template<size_t SIZE, typename ELEM_TYPE>
    using Vec = Matrix<1lu, SIZE, ELEM_TYPE>;

    // Vec2
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 2lu, ELEM_TYPE>; 
    template<typename ELEM_TYPE>
    using Vec2 = Matrix<1lu, 2lu, ELEM_TYPE>;
    using Vec2f = Vec2<float>;

    // Vec3
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 3lu, ELEM_TYPE>; 
    template<typename ELEM_TYPE>
    using Vec3 = Matrix<1lu, 3lu, ELEM_TYPE>;
    using Vec3f = Vec3<float>;

    // Vec4
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 4lu, ELEM_TYPE>;
    template<typename ELEM_TYPE>
    using Vec4  = Matrix<1lu, 4lu, ELEM_TYPE>;
    using Vec4f = Vec4<float>; 
}

#endif 