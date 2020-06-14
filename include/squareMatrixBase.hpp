#ifndef _SQUARE_MATRIX_BASE_HPP_
#define _SQUARE_MATRIX_BASE_HPP_

#include "baseMatrix.hpp"

namespace Core::Maths
{
    template<size_t SIZE, typename ELEM_TYPE>
    class SquareMatrix;

    template<class CHILD, size_t SIZE, typename ELEM_TYPE>
    class SquareMatrixBase : public BaseMatrix<CHILD, SIZE, SIZE, ELEM_TYPE>
    {
    protected:
        using Super            = BaseMatrix<CHILD, SIZE, SIZE, ELEM_TYPE>; 
        using SelfType         = SquareMatrixBase<CHILD, SIZE, ELEM_TYPE>;
        // using SquareMatrixEq   = SquareMatrixBase<CHILD, SIZE, ELEM_TYPE>;
        using ChildType        = CHILD;

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

        static inline constexpr void raiseAsserts() noexcept
        {
            Super::raiseAsserts();
        }

        inline constexpr operator Core::Maths::SquareMatrix<SelfType::getSize(), typename Super::ElemType>() noexcept
        {
            return * reinterpret_cast<Core::Maths::SquareMatrix<SelfType::getSize(), typename Super::ElemType>*> (this);
        }
    };
}

#include "squareMatrixBase.inl"

#endif



    //     template<typename OTHER_MATRIX,
    //              typename = std::enable_if<OTHER_MATRIX::getNbColumns() = 1 
    //                                     && isMatrix<OTHER_MATRIX> 
    //                                     && isMultiplicationPossible<OTHER_MATRIX>()>,
    //              ENABLE_IF_SQUARED>
    //     inline SelfType resolveEquation(const OTHER_MATRIX& result) const noexcept;

    //     template<ENABLE_IF_SQUARED>
    //     static constexpr SelfType identity() noexcept;

    //     #undef ENABLE_IF_SQUARED

    //     // ============================================= //
    //     // ================= MATRIX4x4 ================= //
    //     // ============================================= //

    // public:
    //     inline static constexpr bool isMat4()
    //     {
    //         return (getNbRows() == 4 && getNbColumns() == 4);
    //     }

    //     #define ENABLE_IF_MATRIX4X4 typename SELF_TYPE = SelfType, typename = std::enable_if_t<(SELF_TYPE::isMat4())>

    //     template<ENABLE_IF_MATRIX4X4>
    //     inline constexpr const Matrix<1, 3, ELEM_TYPE>& getXAxis() const noexcept
    //     {
    //         return getRow(0);
    //     }

    //     template<ENABLE_IF_MATRIX4X4>
    //     inline constexpr const Matrix<1, 3, ELEM_TYPE>& getYAxis() const noexcept
    //     {
    //         return getRow(1);
    //     }

    //     template<ENABLE_IF_MATRIX4X4>
    //     inline constexpr const Matrix<1, 3, ELEM_TYPE>& getZAxis() const noexcept
    //     {
    //         return getRow(2);
    //     }

    //     template<ENABLE_IF_MATRIX4X4>
    //     inline constexpr const Matrix<1, 3, ELEM_TYPE>& getTranslation() const noexcept
    //     {
    //         // return reinterpret_cast<> getRow(3);
    //     }