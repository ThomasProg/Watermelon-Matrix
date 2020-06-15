#include "baseSquareMatrix.hpp"

#define _BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS template<class CHILD, size_t SIZE, typename ELEM_TYPE> 
#define _BASE_SQUARE_MATRIX Core::Maths::BaseSquareMatrix<CHILD, SIZE, ELEM_TYPE>
#define _BASE_SQUARE_MATRIX_EQ typename _BASE_SQUARE_MATRIX::EqType

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
constexpr void _BASE_SQUARE_MATRIX::copyDiagonaleFrom(const _BASE_SQUARE_MATRIX& copiedFrom) noexcept
{
    for (size_t i = 0; i < getSize(); i++)
    {
        this->getElements()[i * getSize() + i] = copiedFrom.getElements()[i * getSize() + i];
    }
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
constexpr void _BASE_SQUARE_MATRIX::setDiagonaleTo(const ELEM_TYPE& value) noexcept
{
    for (size_t i = 0; i < getSize(); i++)
    {
        this->getElements()[i * getSize() + i] = value;
    }
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
inline constexpr size_t _BASE_SQUARE_MATRIX::getSize() noexcept
{
    // // _BASE_SQUARE_MATRIX_ASSERT

    // Could also return getNbRows(), the decision is arbitrary. 
    return SIZE;
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::getTransposed() const noexcept
{
    _BASE_SQUARE_MATRIX_EQ returnedMatrix;

    for (size_t i = 0; i < getSize(); i++)
    {
        for (size_t j = i + 1; j < getSize(); j++)
        {
            // Copy top right hand corner.
            returnedMatrix.getElements()[i * getSize() + j] = this->getElements()[j * getSize() + i];

            // Copy bottom left hand corner.
            returnedMatrix.getElements()[j * getSize() + i] = this->getElements()[i * getSize() + j];
        }
    }

    returnedMatrix.copyDiagonaleFrom(*this);

    return returnedMatrix;
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
constexpr _BASE_SQUARE_MATRIX& _BASE_SQUARE_MATRIX::transpose() noexcept
{
    for (size_t i = 0; i < getSize(); i++)
    {
        for (size_t j = i + 1; j < getSize(); j++)
        {
            std::swap(this->getElements()[i * getSize() + j], this->getElements()[j * getSize() + i]);
        }
    }

    return *this;
}



_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::identity() noexcept
{
    EqType returnedMatrix = Core::Maths::BaseSquareMatrix<SelfType, getSize(), ELEM_TYPE>::zero();

    for (size_t i = 0; i < getSize(); i++)
    {
        returnedMatrix.getElements()[i * getSize() + i] = static_cast<ELEM_TYPE> (1);
    }

    return returnedMatrix;
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
template<size_t SELF_SIZE>
constexpr ELEM_TYPE _BASE_SQUARE_MATRIX::getDeterminant(typename std::enable_if<(SELF_SIZE == 1)>::type*) const noexcept
{
    return this->getElements()[0];
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS  
template<size_t SELF_SIZE>
constexpr ELEM_TYPE _BASE_SQUARE_MATRIX::getDeterminant(typename std::enable_if<(SELF_SIZE > 1)>::type*) const noexcept
{
    ElemType det = static_cast<ElemType>(0);
    
    float sign = 1.f;
    for (size_t i = 0; i < getSize(); i++)
    {
        Core::Maths::Matrix<getSize() - 1, getSize() - 1, ElemType> subMatrix = (this->getSubMatrix(i, 0));
        det += (*this)[i][0] * subMatrix.getDeterminant() * sign;
        sign *= -1;
    }

    return det;
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr bool _BASE_SQUARE_MATRIX::isOrthogonal() const noexcept
{
    return (*this) * this->getTransposed() == this->identity();
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE _BASE_SQUARE_MATRIX::getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
{
    // TODO : Sfinae
    return Core::Maths::BaseSquareMatrix<SelfType, getSize() - 1, ElemType>(this->getSubMatrix(excludedRowIndex, excludedColumnIndex)).getDeterminant();
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE _BASE_SQUARE_MATRIX::getCofactor(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
{
    return (excludedRowIndex + excludedColumnIndex) % 2 == 0 ? // condition
            getMinorant(excludedRowIndex, excludedColumnIndex) 
            : 
            - getMinorant(excludedRowIndex, excludedColumnIndex);
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::getComatrix() const noexcept
{
    _BASE_SQUARE_MATRIX_EQ comatrix;

    for (size_t i = 0; i < this->getNbRows(); i++)
    {
        for (size_t j = 0; j < this->getNbColumns(); j++)
        {
            comatrix[i][j] = getCofactor(i, j);
        }
    }

    return comatrix;
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::getAdjoint() const noexcept
{
    return getComatrix().transpose();
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::getInverse() const noexcept
{
    return getAdjoint() / getDeterminant();
}

_BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS
template<typename OTHER_MATRIX>
inline constexpr _BASE_SQUARE_MATRIX_EQ _BASE_SQUARE_MATRIX::resolveEquation(const OTHER_MATRIX& result) const noexcept
{    
    static_assert(OTHER_MATRIX::getNbColumns() == 1, "Columns number shall be 1. If it is not, then it is not an Equation."); // TODO : is this true ?
    static_assert(this->getNbColumns() == OTHER_MATRIX::getNbRows(), "Multiplication is not possible ; matrix sizes are not coherent."); // is multiplication possible
        // TODO : isMultiplicationPossible
    // constexpr bool b = _BASE_SQUARE_MATRIX::isMultiplicationPossible<OTHER_MATRIX>();
    // static_assert(b, "ay");

    return result * getInverse();
}



#undef _BASE_SQUARE_MATRIX_EQ 
#undef _BASE_SQUARE_MATRIX 
#undef _BASE_SQUARE_MATRIX_TEMPLATE_PARAMETERS 