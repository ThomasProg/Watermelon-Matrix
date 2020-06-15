#ifndef _SQUARE_MATRIX_HPP_
#define _SQUARE_MATRIX_HPP_

#include "matrix.hpp"
#include "baseSquareMatrix.hpp"

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    class Matrix<SIZE, SIZE, ELEM_TYPE> : public BaseSquareMatrix<Matrix<SIZE, SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>
    {
    protected:
        using SelfType = Matrix<SIZE, SIZE, ELEM_TYPE>;
        using Super = BaseSquareMatrix<Matrix<SIZE, SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>;

        using ElemType = typename Super::ElemType;

    public:
        union
        {
            ElemType elements[SelfType::getNbElements()];
            std::array<ElemType, SelfType::getNbElements()> array = {};
        };

        inline constexpr Matrix() noexcept __attribute__((always_inline)) 
            : array()
        {

        }
    };

    template<size_t SIZE, typename ELEM_TYPE>
    using SquareMatrix = Matrix<SIZE, SIZE, ELEM_TYPE>;
}

#endif 