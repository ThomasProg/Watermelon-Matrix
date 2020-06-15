#ifndef _BASE_SQUARE_MATRIX_HPP_
#define _BASE_SQUARE_MATRIX_HPP_

#include "baseMatrix.hpp"

namespace Core::Maths
{
    template<class CHILD, size_t SIZE, typename ELEM_TYPE>
    class BaseSquareMatrix : public BaseMatrix<CHILD, SIZE, SIZE, ELEM_TYPE>
    {
    protected:
        // Parent Type
        using Super            = BaseMatrix<CHILD, SIZE, SIZE, ELEM_TYPE>; 
        // Type of the current Matrix
        using SelfType         = BaseSquareMatrix<CHILD, SIZE, ELEM_TYPE>;
        // Equivalent Type
        using EqType           = Matrix<SIZE, SIZE, ELEM_TYPE>;
        using ElemType  = ELEM_TYPE;

    protected:
        constexpr void copyDiagonaleFrom(const SelfType& copiedFrom) noexcept;
        constexpr void setDiagonaleTo(const ELEM_TYPE& value) noexcept;

    public:
        inline static constexpr size_t getSize() noexcept;

        constexpr EqType  getTransposed() const noexcept;
        constexpr SelfType& transpose() noexcept;

        template<size_t SELF_SIZE = SIZE>
        constexpr ELEM_TYPE getDeterminant(typename std::enable_if<(SELF_SIZE > 1)>::type* = nullptr) const noexcept; // stops recursion
        template<size_t SELF_SIZE = SIZE>
        constexpr ELEM_TYPE getDeterminant(typename std::enable_if<(SELF_SIZE == 1)>::type* = nullptr) const noexcept; // recursive function

        inline constexpr bool isOrthogonal() const noexcept;
        inline constexpr ELEM_TYPE getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept;
        inline constexpr ELEM_TYPE  getCofactor(size_t column, size_t line) const noexcept;
        constexpr EqType getComatrix() const noexcept;
        inline constexpr EqType getAdjoint() const noexcept;
        inline constexpr EqType getInverse() const noexcept;

        template<typename OTHER_MATRIX>
        inline constexpr EqType resolveEquation(const OTHER_MATRIX& result) const noexcept;

        static constexpr EqType identity() noexcept;

        static inline constexpr void raiseAsserts() noexcept
        {
            Super::raiseAsserts();
        }
    };
}

#include "baseSquareMatrix.inl"

#endif
