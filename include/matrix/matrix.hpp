#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "baseMatrix.hpp"

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix : public BaseMatrix<Matrix<ROWS, COLUMNS, ELEM_TYPE>, ROWS, COLUMNS, ELEM_TYPE>
    {
    protected:
        using SelfType = Matrix<ROWS, COLUMNS, ELEM_TYPE>;
        using Super = BaseMatrix<Matrix<ROWS, COLUMNS, ELEM_TYPE>, ROWS, COLUMNS, ELEM_TYPE>;

        using ElemType = typename Super::ElemType;

    public:
        union
        {
            ElemType elements[SelfType::getNbElements()];
            std::array<ElemType, SelfType::getNbElements()> array = {};
        };

        inline constexpr Matrix() __attribute__((always_inline))
            : array()
        {

        }
    };
}

#endif 