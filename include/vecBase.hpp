#ifndef _VEC_BASE_HPP_
#define _VEC_BASE_HPP_

#include "baseMatrix.hpp"
#include <array>

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    struct VecBase : public Matrix<1, SIZE, ELEM_TYPE>
    {
        using SelfType = VecBase<SIZE, ELEM_TYPE>;
        using Super    = Matrix<1, SIZE, ELEM_TYPE>; 
    };
}

#endif