#ifndef _BASE_VEC_HPP_
#define _BASE_VEC_HPP_

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
        using EqType           = Matrix<SIZE, 1lu, ELEM_TYPE>;
        using ElemType         = ELEM_TYPE;

    public:
        inline static constexpr ElemType dotProduct(const SelfType& lhs, 
                                                    const SelfType& rhs) noexcept;

        /**
         * @brief 
         * 
         * @return The square length of the vector.
         */
        inline constexpr ElemType sqrLength() const noexcept;

        /**
         * @brief 
         * 
         * @return The length of the vector.
         */
        inline constexpr ElemType length()    const noexcept;

        // SIZE SHOULD NOT BE NULL
        inline constexpr void normalize();
        // SIZE SHOULD NOT BE NULL
        inline constexpr SelfType getNormalized() const;

		inline constexpr float operator[](size_t index) const noexcept
		{
			assert(index < SelfType::getSize());
			return SelfType::getElements()[index];
		}

		inline constexpr float& operator[](size_t index) noexcept
		{
			assert(index < SelfType::getSize());
			return SelfType::getElements()[index];
        }
    };
}

#include "baseVec.inl"

#endif