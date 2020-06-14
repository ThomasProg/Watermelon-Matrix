#ifndef _VEC_HPP_
#define _VEC_HPP_

#include "matrixBase.hpp"
#include <array>

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    struct Vec 
    {
        union 
        {
            struct 
            {
                ELEM_TYPE x, y, z;
            };

            Matrix<1, SIZE, ELEM_TYPE> mat;

            std::array<ELEM_TYPE, SIZE> components; 
        };
    };
}

#endif