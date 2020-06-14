#ifndef _SQUARE_MATRIX_HPP_
#define _SQUARE_MATRIX_HPP_

#include "squareMatrixBase.hpp"

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    class SquareMatrix : public SquareMatrixBase<SquareMatrix<SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>
    {
    protected:
        using SelfType = SquareMatrix<SIZE, ELEM_TYPE>;
        using Super = SquareMatrixBase<SquareMatrix<SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>;

        using ElemType = typename Super::ElemType;

    public:
        union
        {
            ElemType elements[SelfType::getNbElements()] = {};
            std::array<ElemType, SelfType::getNbElements()> array;
        };

    public:
        static inline constexpr void raiseAsserts() noexcept
        {
            Super::raiseAsserts();
        }

        
    };
}

#endif 