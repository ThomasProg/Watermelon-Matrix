#include "baseVec.hpp"
#include "matrix.hpp"
#include "squareMatrix.hpp"
#include "vec3.hpp"
#include <cmath>

#define BASE_VEC_TEMPLATE_PARAMETERS template<class CHILD, size_t SIZE, typename ELEM_TYPE> 
#define BASE_VEC Core::Maths::BaseVec<CHILD, SIZE, ELEM_TYPE>
#define BASE_VEC_EQ typename BASE_VEC::EqType

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE BASE_VEC::dotProduct(const BASE_VEC& lhs, const BASE_VEC& rhs) noexcept
{
    ElemType dot = static_cast<ElemType>(0);
    for (size_t i = 0; i < SelfType::getNbElements(); i++)
    {
        dot += lhs.getElements()[i] * rhs.getElements()[i];
    }
    return dot;
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE BASE_VEC::sqrLength() const noexcept
{
    return dotProduct(*this, *this);
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr BASE_VEC_EQ BASE_VEC::getNormal() const
{
    return (*this) / length();
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr void BASE_VEC::normalize()
{
    this->getElements() = getNormal().getElements();
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr BASE_VEC_EQ BASE_VEC::getNormalSafe() const
{
    const float sqrLength = this->sqrLength();
    return (sqrLength == 0.f) ? Super::zero() : ((*this) / std::sqrt(sqrLength));
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr void BASE_VEC::normalizeSafe()
{
    this->getElements() = this->getNormalSafe().getElements();
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE BASE_VEC::length() const noexcept
{
    // Will use std::sqrt for default types,
    // and sqrt() for user defined types.
    using std::sqrt;
    return sqrt(sqrLength());
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr float BASE_VEC::operator[](size_t index) const noexcept
{
    assert(index < SelfType::getSize());
    return SelfType::getElements()[index];
}

BASE_VEC_TEMPLATE_PARAMETERS
inline constexpr float& BASE_VEC::operator[](size_t index) noexcept
{
    assert(index < SelfType::getSize());
    return SelfType::getElements()[index];
}

#undef BASE_VEC_TEMPLATE_PARAMETERS 
#undef BASE_VEC
#undef BASE_VEC_EQ