#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include "baseVec.hpp"
#include "matrixForwardDecl.hpp"

namespace Core::Maths
{
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

        __inline constexpr Matrix()
            : array()
        {

        }

        inline constexpr Matrix(const ELEM_TYPE& m1, 
                                const ELEM_TYPE& m2, 
                                const ELEM_TYPE& m3, 
                                const ELEM_TYPE& m4) noexcept
            : array({m1, m2, m3, m4})
        {

        }
    };
}

#endif