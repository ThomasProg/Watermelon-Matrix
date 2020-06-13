#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix;

    template<size_t SIZE, typename ELEM_TYPE>
    using SquareMatrix = Matrix<SIZE, SIZE, ELEM_TYPE>;

    template<size_t SIZE, typename ELEM_TYPE>
    using SquareMatrix = Matrix<SIZE, SIZE, ELEM_TYPE>;

    template<typename ELEM_TYPE>
    using Vec3 = Matrix<1, 3, ELEM_TYPE>;

    using Vec3f = Matrix<1, 3, float>;

    // TODO : put private
    class MatrixBase 
    {
    protected:
        ~MatrixBase() = default; // forbids instanciation
    };

    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix : private MatrixBase
    {
    protected:
        using SelfType = Matrix<ROWS, COLUMNS, ELEM_TYPE>;

    public:
        using ElemType = ELEM_TYPE;

        // ========================================== //
        // ================= MATRIX ================= //
        // ========================================== //

        inline static constexpr size_t getNbRows()     noexcept;
        inline static constexpr size_t getNbColumns()  noexcept;
        inline static constexpr size_t getNbElements() noexcept;

        ElemType elements[ROWS * COLUMNS] = {};

        inline constexpr Matrix() noexcept = default;
        inline constexpr Matrix(const SelfType&) noexcept = default;
        inline constexpr Matrix(SelfType&&) noexcept = default;
        inline ~Matrix() noexcept = default;

        constexpr SelfType& operator=(const SelfType&) noexcept = default;
        constexpr SelfType& operator=(SelfType&&)      noexcept = default;

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
        using EnableIfMatrix = std::enable_if_t<std::is_base_of<MatrixBase, OTHER_MATRIX>::value>;

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

        // ================================================== //
        // ================= SQUARED MATRIX ================= //
        // ================================================== //

    public:
        inline static constexpr bool isSquared()
        {
            return (getNbRows() == getNbColumns());
        }

    private:
        template<typename MATRIX>
        using EnableIfSquared = std::enable_if_t<MATRIX::isSquared()>;

        #define ENABLE_IF_SQUARED typename SELF_TYPE = SelfType, typename = EnableIfSquared<SELF_TYPE>

    private:
        template<ENABLE_IF_SQUARED>
        constexpr void copyDiagonaleFrom(const SelfType& copiedFrom) noexcept;

        template<ENABLE_IF_SQUARED>
        constexpr void setDiagonaleTo(const ElemType& value) noexcept;

    public:
        template<typename SELF_TYPE = SelfType>
        inline static constexpr size_t getSize() noexcept;

        template<ENABLE_IF_SQUARED>
        constexpr SelfType getTransposed() const noexcept;

        template<ENABLE_IF_SQUARED>
        constexpr SelfType& transpose() noexcept;

        template<ENABLE_IF_SQUARED, size_t SIZE = getSize()>
        constexpr ElemType getDeterminant(typename std::enable_if<(SIZE > 1)>::type* = nullptr) const noexcept; // stops recursion

        template<ENABLE_IF_SQUARED, size_t SIZE = getSize()>
        constexpr ElemType getDeterminant(typename std::enable_if<(SIZE == 1)>::type* = nullptr) const noexcept; // recursive function

        template<ENABLE_IF_SQUARED>
        inline constexpr bool isOrthogonal() const noexcept;

        template<ENABLE_IF_SQUARED>
        inline constexpr ElemType getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept;

        template<ENABLE_IF_SQUARED>
        inline ElemType  getCofactor(size_t column, size_t line) const noexcept;

        template<ENABLE_IF_SQUARED>
        SelfType getComatrix() const noexcept;

        template<ENABLE_IF_SQUARED>
        inline SelfType getAdjoint() const noexcept;

        template<ENABLE_IF_SQUARED>
        inline SelfType getInverse() const noexcept;

        template<typename OTHER_MATRIX,
                 typename = std::enable_if<OTHER_MATRIX::getNbColumns() = 1 
                                        && isMatrix<OTHER_MATRIX> 
                                        && isMultiplicationPossible<OTHER_MATRIX>()>,
                 ENABLE_IF_SQUARED>
        inline SelfType resolveEquation(const OTHER_MATRIX& result) const noexcept;

        template<ENABLE_IF_SQUARED>
        static constexpr SelfType identity() noexcept;

        #undef ENABLE_IF_SQUARED

        // ============================================= //
        // ================= MATRIX4x4 ================= //
        // ============================================= //

    public:
        inline static constexpr bool isMat4()
        {
            return (getNbRows() == 4 && getNbColumns() == 4);
        }

        #define ENABLE_IF_MATRIX4X4 typename SELF_TYPE = SelfType, typename = std::enable_if_t<(SELF_TYPE::isMat4())>

        template<ENABLE_IF_MATRIX4X4>
        inline constexpr const Matrix<1, 3, ELEM_TYPE>& getXAxis() const noexcept
        {
            return getRow(0);
        }

        template<ENABLE_IF_MATRIX4X4>
        inline constexpr const Matrix<1, 3, ELEM_TYPE>& getYAxis() const noexcept
        {
            return getRow(1);
        }

        template<ENABLE_IF_MATRIX4X4>
        inline constexpr const Matrix<1, 3, ELEM_TYPE>& getZAxis() const noexcept
        {
            return getRow(2);
        }

        template<ENABLE_IF_MATRIX4X4>
        inline constexpr const Matrix<1, 3, ELEM_TYPE>& getTranslation() const noexcept
        {
            // return reinterpret_cast<> getRow(3);
        }

        // inline constexpr Matrix<1, 3, ELEM_TYPE> getSquaredScale() const noexcept
        // {
        //     Vec3{getXAxis().getSquaredLength(), getYAxis().getSquaredLength(), getZAxis().getSquaredLength()};
        // }

        // inline constexpr Matrix<1, 3, ELEM_TYPE> getScale() const noexcept
        // {
        //     Vec3{getXAxis().vectorLength(), getYAxis().vectorLength(), getZAxis().vectorLength()};
        // }

        // // void normalizeScale();
        // // Matrix4x4 getInverse() const;

        // static Matrix4x4 getProjectionMatrixOnZAxis(const float d);
        // static Matrix4x4 CreatePerspectiveProjectionMatrix(int width, int height,float near,float far,float fov);
        // static Core::Maths::Matrix4x4 lookAt(const Core::Maths::Vec3& eye, const Core::Maths::Vec3& center, const Core::Maths::Vec3& up);

        // static Matrix4x4 CreateScaleMatrix(Vec3 scale);
        // static Matrix4x4 CreateTranslationMatrix(Vec3 translation);

        // static Matrix4x4 CreateXRotationMatrix(float angleX);
        // static Matrix4x4 CreateYRotationMatrix(float angleY);
        // static Matrix4x4 CreateZRotationMatrix(float angleZ);

        // static Matrix4x4 CreateFixedAngleEulerRotationMatrix(Vec3 angles);

        // static Matrix4x4 CreateTRSMatrix(Vec3 scale, Vec3 translation, Vec3 angles);
        // static Matrix4x4 CreateTRSMatrix(const Physics::Transform& transform);

        // static Matrix4x4 CreateAxisRotationMatrix(const Vec3& axis, float angle); 
        #undef ENABLE_IF_MATRIX4X4
    };


    template<size_t RHS_ROWS, size_t RHS_COLUMNS, typename RHS_ELEM_TYPE>
    std::ostream& operator<<(std::ostream& stream, const Core::Maths::Matrix<RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs);
}

#include "matrix.inl"
#include "squareMatrix.inl"
#include "matrix4x4.inl"

#endif