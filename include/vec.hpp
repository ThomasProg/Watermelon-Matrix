#ifndef _VEC_HPP_
#define _VEC_HPP_

#include "baseVec.hpp"
#include "matrixForwardDecl.hpp"

namespace Core::Maths
{
    // forward declaration
    template<typename ELEM_TYPE>
    struct Matrix<1lu, 2lu, ELEM_TYPE>;

    // Vec2 alias
    template<size_t SIZE, typename ELEM_TYPE>
    using Vec = Matrix<1lu, SIZE, ELEM_TYPE>;

    template<size_t SIZE, typename ELEM_TYPE>
    struct Matrix<1lu, SIZE, ELEM_TYPE> : public BaseVec<Vec2<ELEM_TYPE>, SIZE, ELEM_TYPE>
    {
        using SelfType = Vec2<ELEM_TYPE>;
        using Super    = BaseVec<SelfType, SIZE, ELEM_TYPE>; 

        union 
        {
            ELEM_TYPE elements[SelfType::getNbElements()];
            std::array<ELEM_TYPE, SelfType::getNbElements()> array; 
        };

        inline constexpr Matrix() __attribute__((always_inline))
            : array()
        {

        }

    };
}

#endif