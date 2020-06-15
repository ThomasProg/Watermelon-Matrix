#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include "baseVec.hpp"

namespace Core::Maths
{
    // forward declaration
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 3lu, ELEM_TYPE>;

    // Vec3 alias
    template<typename ELEM_TYPE>
    using Vec3 = Matrix<1lu, 3lu, ELEM_TYPE>;
    using Vec3f = Vec3<float>;

    template<typename ELEM_TYPE>
    struct Matrix<1lu, 3lu, ELEM_TYPE> : public BaseVec<Vec3<ELEM_TYPE>, 3lu, ELEM_TYPE>
    {
        using SelfType = Vec3<ELEM_TYPE>;
        using Super    = BaseVec<SelfType, 3lu, ELEM_TYPE>; 

        union 
        {
            // ANONYMOUS STRUCT : NON STANDARD !
            struct 
            {
                ELEM_TYPE x, y, z;
            };

            std::array<ELEM_TYPE, SelfType::getNbElements()> array; 
        };

        inline constexpr Matrix() __attribute__((always_inline))
            : array()
        {

        }

        inline static constexpr SelfType crossProduct(const SelfType& lhs, 
                                                      const SelfType& rhs) noexcept
        {
            return 
            {
                lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x
            };
        }

        inline constexpr Matrix(const ELEM_TYPE& m1, 
                                const ELEM_TYPE& m2, 
                                const ELEM_TYPE& m3) noexcept
            : array({m1, m2, m3})
        {

        }
    };
}

#endif