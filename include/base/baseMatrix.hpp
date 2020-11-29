#ifndef _BASE_MATRIX_HPP_
#define _BASE_MATRIX_HPP_

#include <iostream>
#include <array>
#include <cassert>

#include "matrixForwardDecl.hpp"

#define CORRECT_MATRIX_ASSERT(mat) static_assert(sizeof(mat) >= mat::childrenMinSizeof())

namespace Core::Maths
{
    /**
     * @brief This class should NOT be instancied. It should only be inheriting from.
     * 
     * @tparam CHILD        : The type of the class inheriting this class.
     * @tparam ROWS         : The number of rows this matrix should have.
     * @tparam COLUMNS      : The number of columns this matrix should have.
     * @tparam ELEM_TYPE    : The type this matrix should store.
     */
    template<class CHILD, size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class BaseMatrix 
    {
    protected:
        // Type of the current Matrix
        using SelfType  = BaseMatrix<CHILD, ROWS, COLUMNS, ELEM_TYPE>;
        // Equivalent Type
        using EqType    = Matrix<ROWS, COLUMNS, ELEM_TYPE>;
        using ElemType  = ELEM_TYPE;

    public:
        inline static constexpr size_t getNbRows()     noexcept;
        inline static constexpr size_t getNbColumns()  noexcept;
        inline static constexpr size_t getNbElements() noexcept;

        __inline constexpr std::array<ElemType, SelfType::getNbElements()>& getElements() noexcept;
        __inline constexpr const std::array<ElemType, SelfType::getNbElements()>& getElements() const noexcept;

        // We protect constructors to prevent the class instantiation.
    protected: 
        inline constexpr BaseMatrix() noexcept = default;
        inline constexpr BaseMatrix(const SelfType& rhs) noexcept = default;
        inline constexpr BaseMatrix(SelfType&& rhs) noexcept = default;
        inline ~BaseMatrix() noexcept = default;
        constexpr SelfType& operator=(const SelfType& rhs) noexcept = default;
        constexpr SelfType& operator=(SelfType&& rhs)      noexcept = default;

    public:
        constexpr EqType operator+(const SelfType& rhs) noexcept;
        constexpr EqType operator-(const SelfType& rhs) noexcept;
        constexpr EqType operator*(const SelfType& rhs) const noexcept;
        constexpr EqType operator*(ElemType f) const noexcept;
        constexpr EqType operator/(ElemType f) const noexcept;
        constexpr SelfType& operator*=(ElemType f) noexcept;
        constexpr SelfType& operator/=(ElemType f) noexcept;
        constexpr ElemType const * operator[](size_t id) const noexcept;
        constexpr ElemType* operator[](size_t id) noexcept;

        constexpr EqType operator-() noexcept;

        inline constexpr       Matrix<1, COLUMNS, ELEM_TYPE>& getRow(size_t index)       noexcept;
        inline constexpr const Matrix<1, COLUMNS, ELEM_TYPE>& getRow(size_t index) const noexcept;

        constexpr bool operator==(const SelfType& rhs) const noexcept;
        constexpr bool operator!=(const SelfType& rhs) const noexcept;

        template<typename OTHER_MATRIX>
        inline static constexpr bool isMatrix();

        template<typename OTHER_MATRIX>
        using EnableIfMatrix = std::enable_if_t<std::is_base_of<BaseMatrix, OTHER_MATRIX>::value>;

        template<typename OTHER_MATRIX, typename = EnableIfMatrix<OTHER_MATRIX>>
        inline static constexpr bool isMultiplicationPossible();

        template<typename OTHER_MATRIX>
        using EnableIfMultiplicationPossible = std::enable_if<isMultiplicationPossible<OTHER_MATRIX>()>;

        template<typename OTHER_MATRIX, // template args
            typename = EnableIfMultiplicationPossible<OTHER_MATRIX>> // sfinae conditions
        constexpr Core::Maths::Matrix<ROWS, OTHER_MATRIX::getNbColumns(), ElemType> // return type
            operator*(const OTHER_MATRIX& rhs) const noexcept;

        template<size_t SELF_ROWS    = getNbRows(), 
                 size_t SELF_COLUMNS = getNbColumns(), 
                 typename = std::enable_if_t<(SELF_ROWS > 0) && (SELF_COLUMNS > 0)>>
        constexpr Matrix<ROWS - 1, COLUMNS - 1, ElemType> getSubMatrix(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept;

        static constexpr EqType zero() noexcept;

        static constexpr size_t childrenMinSizeof() noexcept
        {
            return getNbColumns() * getNbRows() * sizeof(ElemType);
        }

        template<typename TESTED_TYPE, typename OTHER_TYPE>
        static constexpr bool isValid()
        {
            return std::is_same<std::remove_const_t<TESTED_TYPE>, std::remove_const_t<OTHER_TYPE>>::value;
        }

        static inline constexpr void raiseAsserts() noexcept
        {
            constexpr ElemType elementsAssertion[ROWS * COLUMNS] = {};
            constexpr std::array<ElemType, ROWS * COLUMNS> arrayAssertion = {};

            static_assert(SelfType::isValid<decltype(CHILD::elements), decltype(elementsAssertion)>(), "NOOO");
            static_assert(SelfType::isValid<decltype(CHILD::array),    decltype(arrayAssertion)>()   , "NOOO");
            
            static_assert((!std::is_final<CHILD>::value) || sizeof(CHILD) >= CHILD::childrenMinSizeof(), 
                        "The size of the class must be atleast CHILD::childrenMinSizeof() bytes. Else, MatrixBase wouldn't work correctly.");
            static_assert(std::is_standard_layout<CHILD>(), "CHILD should have a standard layout, or parent functions would be unspecified.");
        }
    };

    template<typename RHS_CHILD, size_t RHS_ROWS, size_t RHS_COLUMNS, typename RHS_ELEM_TYPE>
    constexpr Matrix<RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE> operator*(float lhs, const Core::Maths::BaseMatrix<RHS_CHILD, RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs) 
    {
        Matrix<RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE> result;
        for (size_t i = 0; i < rhs.getNbElements(); i++)
        {
            result[i] = lhs * rhs.getElements()[i];
        }
        return result;
    }

    template<typename RHS_CHILD, size_t RHS_ROWS, size_t RHS_COLUMNS, typename RHS_ELEM_TYPE>
    std::ostream& operator<<(std::ostream& stream, const Core::Maths::BaseMatrix<RHS_CHILD, RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs);
}

#include "baseMatrix.inl"

#endif