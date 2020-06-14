#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include "matrixBase.hpp"

namespace Core::Maths
{
    template<typename ELEM_TYPE>
    struct Vec3 : public VecBase<3, ELEM_TYPE>
    {
        using SelfType = Vec3<ELEM_TYPE>;
        using Super    = VecBase<3, ELEM_TYPE>; 

        union 
        {
            // ANONYMOUS STRUCT : NON STANDARD !
            struct 
            {
                ELEM_TYPE x, y, z;
            };

            ELEM_TYPE* ptr;

            std::array<ELEM_TYPE, SelfType::getNbElements()> components; 
        };

        static inline constexpr void raiseAsserts() noexcept
        {
            Super::template raiseAsserts<SelfType>();
        }
    };
}

#endif