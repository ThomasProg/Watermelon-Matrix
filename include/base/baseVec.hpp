#ifndef _BASE_VEC_HPP_
#define _BASE_VEC_HPP_

#include "matrixForwardDecl.hpp"
#include "baseMatrix.hpp"
#include <array>

namespace Core::Maths
{
    template<class CHILD, size_t SIZE, typename ELEM_TYPE>
    struct BaseVec : public BaseMatrix<CHILD, 1lu, SIZE, ELEM_TYPE>
    {
    protected:
        // Parent Type
        using Super            = BaseMatrix<CHILD, 1, SIZE, ELEM_TYPE>;
        // Type of the current Matrix
        using SelfType         = BaseVec<CHILD, SIZE, ELEM_TYPE>;
        // Equivalent Type
        using EqType           = Matrix<1lu, SIZE, ELEM_TYPE>;
        using ElemType         = ELEM_TYPE;

    public:
        inline static constexpr ElemType dotProduct(const SelfType& lhs, 
                                                    const SelfType& rhs) noexcept;

        /**
         * @brief Returns the squared length of the vector : x*x + y*y + z*z
         * 
         * @return The square length of the vector.
         */
        inline constexpr ElemType sqrLength() const noexcept;

        /**
         * @brief Returns the length of the vector : sqrt(x*x + y*y + z*z)
         * 
         * @return The length of the vector.
         */
        inline constexpr ElemType length()    const noexcept;

        /* LENGTH SHOULD NOT BE NULL */
        inline constexpr void normalize();
        /* LENGTH SHOULD NOT BE NULL */
        inline constexpr EqType getNormal() const;
        inline constexpr void normalizeSafe();
        inline constexpr EqType getNormalSafe() const;

		inline constexpr float  operator[](size_t index) const noexcept;
		inline constexpr float& operator[](size_t index)       noexcept;
    };
}

#include "baseVec.inl"

#endif