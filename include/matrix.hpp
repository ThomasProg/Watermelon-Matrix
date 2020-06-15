#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "baseMatrix.hpp"
#include "squareMatrix.hpp"

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

    public:
        static inline constexpr void raiseAsserts() noexcept
        {
            Super::raiseAsserts();
        }

        template<size_t SIZE>
        inline constexpr operator SquareMatrix<SIZE, ELEM_TYPE>()
        {
            // static_assert(SIZE == SelfType::getNbRows() && SIZE == SelfType::getNbColumns());
            // BaseMatrix<SelfType, ROWS, COLUMNS, ELEM_TYPE>* temp = static_cast<BaseMatrix<SelfType, ROWS, COLUMNS, ELEM_TYPE>*> (this);
            // SquareMatrixBase<SelfType, ROWS, ELEM_TYPE>* temp2 = reinterpret_cast<SquareMatrixBase<SelfType, ROWS, ELEM_TYPE>*> (this);
            // return * static_cast<SquareMatrix<SIZE, ELEM_TYPE>*> (temp);

            // // TODO : cast at compile time
            SquareMatrix<SIZE, ELEM_TYPE> temp;
            temp.array = this->array;
            return temp; 
        }
    };

    template<size_t SIZE, typename ELEM_TYPE>
    class Matrix<SIZE, SIZE, ELEM_TYPE> : public SquareMatrixBase<SquareMatrix<SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>
    {
    public:
        using SelfType = Matrix<SIZE, SIZE, ELEM_TYPE>;
        using Super = SquareMatrixBase<Matrix<SIZE, SIZE, ELEM_TYPE>, SIZE, ELEM_TYPE>;

        using ElemType = ELEM_TYPE;

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

    public:
        static inline constexpr void raiseAsserts() noexcept
        {
            Super::raiseAsserts();
        }

        // template<size_t SIZE>
        // inline constexpr operator SquareMatrix<SIZE, ELEM_TYPE>()
        // {
        //     // static_assert(SIZE == SelfType::getNbRows() && SIZE == SelfType::getNbColumns());
        //     BaseMatrix<SelfType, ROWS, COLUMNS, ELEM_TYPE>* temp = static_cast<BaseMatrix<SelfType, ROWS, COLUMNS, ELEM_TYPE>*> (this);
        //     SquareMatrixBase<SelfType, ROWS, ELEM_TYPE>* temp2 = reinterpret_cast<SquareMatrixBase<SelfType, ROWS, ELEM_TYPE>*> (this);
        //     return * static_cast<SquareMatrix<SIZE, ELEM_TYPE>*> (temp);

        //     // // TODO : cast at compile time
        //     // SquareMatrix<SIZE, ELEM_TYPE> temp;
        //     // temp.array = this->array;
        //     // return temp; 
        // }
    };
}

#endif 