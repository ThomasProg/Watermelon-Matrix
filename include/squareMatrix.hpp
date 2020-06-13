// #ifndef _SQUARED_MATRIX_HPP_
// #define _SQUARED_MATRIX_HPP_

// #include "matrix.hpp"

// namespace Core::Maths
// {
//     template<size_t SIZE, typename ELEM_TYPE>
//     class SquaredMatrix : public Matrix<SIZE, SIZE, ELEM_TYPE>
//     {
//     protected:
//         using MatType = SquaredMatrix<SIZE, ELEM_TYPE>;

//     protected:
//         constexpr void copyDiagonaleFrom(const MatType& copiedFrom) noexcept;
//         constexpr void setDiagonaleTo(const ELEM_TYPE& value) noexcept;

//     public:
//         inline static constexpr size_t getSize() noexcept;

//         constexpr MatType  getTransposed() const noexcept;
//         constexpr MatType& transpose() noexcept;

//         template<size_t T = SIZE>
//         constexpr ELEM_TYPE getDeterminant(typename std::enable_if<T != 0>::type* = nullptr) const noexcept; // stops recursion
//         template<size_t T = SIZE>
//         constexpr ELEM_TYPE getDeterminant(typename std::enable_if<T == 0>::type* = nullptr) const noexcept; // recursive function

//         inline constexpr bool isOrthogonal() const noexcept;
//         inline constexpr ELEM_TYPE getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept;
//         inline ELEM_TYPE  getCofactor(size_t column, size_t line) const noexcept;
//         MatType getComatrix() const noexcept;
//         inline MatType getAdjoint() const noexcept;
//         inline MatType getInverse() const noexcept;
//         inline MatType resolveEquation(const MatType& result) const noexcept;

//         static constexpr MatType identity() noexcept;
//     };
// }

// #include "squaredMatrix.inl"

// #endif