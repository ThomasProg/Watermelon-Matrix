#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include "baseVec.hpp"

namespace Core::Maths
{
    // forward declaration
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 4lu, ELEM_TYPE>;

    // Vec4 alias
    template<typename ELEM_TYPE>
    using Vec4  = Matrix<1lu, 4lu, ELEM_TYPE>;
    using Vec4f = Vec4<float>;

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 4lu, ELEM_TYPE> : public BaseVec<Vec4<ELEM_TYPE>, 4lu, ELEM_TYPE>
    {
        using SelfType = Vec4<ELEM_TYPE>;
        using Super    = BaseVec<SelfType, 4lu, ELEM_TYPE>; 

        union 
        {
            // ANONYMOUS STRUCT : NON STANDARD !
            struct 
            {
                ELEM_TYPE x, y, z, w;
            };

            std::array<ELEM_TYPE, SelfType::getNbElements()> array; 
        };

        inline constexpr Matrix() __attribute__((always_inline))
            : array()
        {

        }
    };
}

#endif