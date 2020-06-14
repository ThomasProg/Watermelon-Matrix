#ifndef _SQUARE_MATRIX_BASE_HPP_
#define _SQUARE_MATRIX_BASE_HPP_

#include "matrix.hpp"

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    class SquareMatrix;

    template<size_t SIZE, typename ELEM_TYPE>
    class SquareMatrix : public Matrix<SIZE, SIZE, ELEM_TYPE>
    {
    protected:
        using Super            = Matrix<SIZE, SIZE, ELEM_TYPE>; 
        using SelfType         = SquareMatrix<SIZE, ELEM_TYPE>;

    protected:
        constexpr void copyDiagonaleFrom(const SelfType& copiedFrom) noexcept;
        constexpr void setDiagonaleTo(const ELEM_TYPE& value) noexcept;

    public:
        inline static constexpr size_t getSize() noexcept;

        constexpr SelfType  getTransposed() const noexcept;
        constexpr SelfType& transpose() noexcept;

        template<size_t SELF_SIZE = SIZE>
        constexpr ELEM_TYPE getDeterminant(typename std::enable_if<(SELF_SIZE > 1)>::type* = nullptr) const noexcept; // stops recursion
        template<size_t SELF_SIZE = SIZE>
        constexpr ELEM_TYPE getDeterminant(typename std::enable_if<(SELF_SIZE == 1)>::type* = nullptr) const noexcept; // recursive function

        inline constexpr bool isOrthogonal() const noexcept;
        inline constexpr ELEM_TYPE getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept;
        inline constexpr ELEM_TYPE  getCofactor(size_t column, size_t line) const noexcept;
        constexpr SelfType getComatrix() const noexcept;
        inline constexpr SelfType getAdjoint() const noexcept;
        inline constexpr SelfType getInverse() const noexcept;

        template<typename OTHER_MATRIX>
        inline constexpr SelfType resolveEquation(const OTHER_MATRIX& result) const noexcept;

        static constexpr SelfType identity() noexcept;
    };
}

#include "squareMatrix.inl"

#endif