#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include "baseVec.hpp"

namespace Core::Maths
{
    // forward declaration
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 2lu, ELEM_TYPE>;

    // Vec2 alias
    template<typename ELEM_TYPE>
    using Vec2 = Matrix<1lu, 2lu, ELEM_TYPE>;
    using Vec2f = Vec2<float>;

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 2lu, ELEM_TYPE> : public BaseVec<Vec2<ELEM_TYPE>, 2lu, ELEM_TYPE>
    {
        using SelfType = Vec2<ELEM_TYPE>;
        using Super    = BaseVec<SelfType, 2lu, ELEM_TYPE>; 

        union 
        {
            // ANONYMOUS STRUCT : NON STANDARD !
            struct 
            {
                ELEM_TYPE x, y;
            };

            std::array<ELEM_TYPE, SelfType::getNbElements()> array; 
        };

        inline constexpr Matrix() __attribute__((always_inline))
            : array()
        {

        }

        inline constexpr SelfType getNormal() const noexcept
        {
            return { -y, x };
        }

        inline constexpr Matrix(const ELEM_TYPE& m1, 
                                const ELEM_TYPE& m2) noexcept
            : array({m1, m2})
        {

        }
    };
}

#endif