#ifndef _BASE_MATRIX_HPP_
#define _BASE_MATRIX_HPP_

#include <iostream>
#include <array>

#define CORRECT_MATRIX_ASSERT(mat) static_assert(sizeof(mat) >= mat::childrenMinSizeof())

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix;

    template<class CHILD, size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class BaseMatrix 
    {
    protected:
        using SelfType  = BaseMatrix<CHILD, ROWS, COLUMNS, ELEM_TYPE>;

    public:
        using ElemType = ELEM_TYPE;

        // ========================================== //
        // ================= MATRIX ================= //
        // ========================================== //

        inline static constexpr size_t getNbRows()     noexcept;
        inline static constexpr size_t getNbColumns()  noexcept;
        inline static constexpr size_t getNbElements() noexcept;

        // ElemType elements[ROWS * COLUMNS] = {};

        inline constexpr std::array<ElemType, getNbElements()>& getElements() noexcept
        {
            static_assert(std::is_standard_layout<SelfType>(), "Can't convert a non standard layout : return value would be unspecified.");
            static_assert(std::is_standard_layout<std::array<ElemType, (getNbRows() * getNbColumns())>>(), "Can't convert to a non standard layout : return value would be unspecified.");
            return ((reinterpret_cast<CHILD*> (this)) ->array);// reinterpret_cast<ElemType*> (this);
        }

        inline constexpr const std::array<ElemType, getNbElements()>& getElements() const noexcept
        {
            static_assert(std::is_standard_layout<SelfType>(), "Can't convert a non standard layout : return value would be unspecified.");
            static_assert(std::is_standard_layout<std::array<ElemType, (getNbRows() * getNbColumns())>>(), "Can't convert to a non standard layout : return value would be unspecified.");
            return ((reinterpret_cast<const CHILD*> (this)) ->array);// reinterpret_cast<const ElemType*> (this);
        }

    public:
        inline constexpr BaseMatrix() noexcept = default;
        inline constexpr BaseMatrix(const SelfType& rhs) noexcept
        {
            getElements() = rhs.getElements();
        }
        inline constexpr BaseMatrix(SelfType&& rhs) noexcept
        {
            getElements() = std::move(rhs.getElements());
        }
        inline ~BaseMatrix() noexcept = default;
    public:
        constexpr SelfType& operator=(const SelfType& rhs) noexcept
        {
            getElements() = rhs.getElements();
            return *this;
        }

        constexpr SelfType& operator=(SelfType&& rhs)      noexcept
        {
            getElements() = std::move(rhs.getElements());
            return *this;
        }


        constexpr SelfType operator+(const SelfType& rhs) noexcept;
        constexpr SelfType operator-(const SelfType& rhs) noexcept;
        constexpr SelfType operator*(const SelfType& rhs) const noexcept;
        constexpr SelfType operator*(ElemType f) const noexcept;
        constexpr SelfType operator/(ElemType f) const noexcept;
        constexpr SelfType& operator*=(ElemType f) noexcept;
        constexpr SelfType& operator/=(ElemType f) noexcept;
        constexpr ElemType const * operator[](size_t id) const noexcept;
        constexpr ElemType* operator[](size_t id) noexcept;

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

        static constexpr SelfType zero() noexcept;

        template<typename MATRIX, typename = std::enable_if_t<std::is_base_of<SelfType, MATRIX>::value>>
        inline constexpr operator MATRIX() noexcept
        {
            static_assert(std::is_standard_layout<SelfType>(), "Can't convert a non standard layout : return value would be unspecified.");
            static_assert(std::is_standard_layout<MATRIX>(), "Can't convert to a non standard layout : return value would be unspecified.");
            static_assert(sizeof(SelfType) <= sizeof(MATRIX), "Can't convert if return type size is not equal or higher than the current type size.");
            return * reinterpret_cast<MATRIX*> (this);
        }

        inline constexpr operator Core::Maths::Matrix<getNbRows(), getNbColumns(), ElemType>() noexcept
        {
            return * reinterpret_cast<Core::Maths::Matrix<getNbRows(), getNbColumns(), ElemType>*> (this);
        }

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
    std::ostream& operator<<(std::ostream& stream, const Core::Maths::BaseMatrix<RHS_CHILD, RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs);
}

#include "baseMatrix.inl"

#endif