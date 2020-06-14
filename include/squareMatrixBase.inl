#include "squareMatrixBase.hpp"

#define SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS template<class CHILD, size_t SIZE, typename ELEM_TYPE> 
#define SQUARE_MATRIX_BASE Core::Maths::SquareMatrixBase<CHILD, SIZE, ELEM_TYPE>

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS>
constexpr void SQUARE_MATRIX_BASE::copyDiagonaleFrom(const SQUARE_MATRIX_BASE& copiedFrom) noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    for (size_t i = 0; i < getSize(); i++)
    {
        this->getElements()[i * getSize() + i] = copiedFrom.getElements()[i * getSize() + i];
    }
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS>
constexpr void SQUARE_MATRIX_BASE::setDiagonaleTo(const ELEM_TYPE& value) noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    for (size_t i = 0; i < getSize(); i++)
    {
        this->getElements()[i * getSize() + i] = value;
    }
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<typename SelfType>
inline constexpr size_t SQUARE_MATRIX_BASE::getSize() noexcept
{
    // // SQUARE_MATRIX_BASE_ASSERT

    // Could also return getNbRows(), the decision is arbitrary. 
    return SIZE;
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS>
constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::getTransposed() const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    SQUARE_MATRIX_BASE returnedMatrix;

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

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS>
constexpr SQUARE_MATRIX_BASE& SQUARE_MATRIX_BASE::transpose() noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    for (size_t i = 0; i < getSize(); i++)
    {
        for (size_t j = i + 1; j < getSize(); j++)
        {
            std::swap(this->getElements()[i * getSize() + j], this->getElements()[j * getSize() + i]);
        }
    }

    return *this;
}



SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
// template<ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS>
constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::identity() noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    constexpr SQUARE_MATRIX_BASE returnedMatrix = Core::Maths::SquareMatrixBase<SelfType, getSize(), ELEM_TYPE>::zero();

    for (size_t i = 0; i < getSize(); i++)
    {
        returnedMatrix.getElements()[i * getSize() + i] = static_cast<ELEM_TYPE> (1);
    }

    return returnedMatrix;
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
template<size_t SELF_SIZE>
constexpr ELEM_TYPE SQUARE_MATRIX_BASE::getDeterminant(typename std::enable_if<(SELF_SIZE == 1)>::type*) const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    return this->getElements()[0];
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS  
template<size_t SELF_SIZE>
constexpr ELEM_TYPE SQUARE_MATRIX_BASE::getDeterminant(typename std::enable_if<(SELF_SIZE > 1)>::type*) const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    ELEM_TYPE det = static_cast<ELEM_TYPE>(0);
    
    float sign = 1.f;
    for (size_t i = 0; i < getSize(); i++)
    {
        Core::Maths::SquareMatrixBase<SelfType, getSize() - 1, ELEM_TYPE> subMatrix = (this->getSubMatrix(i, 0));
        det += (*this)[i][0] * subMatrix.getDeterminant() * sign;
        sign *= -1;
    }

    return det;
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
inline constexpr bool SQUARE_MATRIX_BASE::isOrthogonal() const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    return (*this) * this->getTransposed() == this->identity();
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE SQUARE_MATRIX_BASE::getMinorant(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    // TODO : Sfinae
    return Core::Maths::SquareMatrixBase<SelfType, SIZE - 1, ELEM_TYPE>(this->getSubMatrix(excludedRowIndex, excludedColumnIndex)).getDeterminant();
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
inline constexpr ELEM_TYPE SQUARE_MATRIX_BASE::getCofactor(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    return (excludedRowIndex + excludedColumnIndex) % 2 == 0 ? // condition
            getMinorant(excludedRowIndex, excludedColumnIndex) 
            : 
            - getMinorant(excludedRowIndex, excludedColumnIndex);
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::getComatrix() const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    SquareMatrixBase<SelfType, getSize(), ELEM_TYPE> comatrix;

    for (size_t i = 0; i < this->getNbRows(); i++)
    {
        for (size_t j = 0; j < this->getNbColumns(); j++)
        {
            comatrix[i][j] = getCofactor(i, j);
        }
    }

    return comatrix;
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
inline constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::getAdjoint() const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    return getComatrix().transpose();
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
inline constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::getInverse() const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT

    return getAdjoint() / getDeterminant();
}

SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS
template<typename OTHER_MATRIX>
inline constexpr SQUARE_MATRIX_BASE SQUARE_MATRIX_BASE::resolveEquation(const OTHER_MATRIX& result) const noexcept
{
    // SQUARE_MATRIX_BASE_ASSERT
    static_assert(OTHER_MATRIX::getNbColumns() == 1, "Columns number shall be 1. If it is not, then it is not an Equation."); // TODO : is this true ?
    static_assert(this->getNbColumns() == OTHER_MATRIX::getNbRows(), "Multiplication is not possible ; matrix sizes are not coherent."); // is multiplication possible
        // TODO : isMultiplicationPossible
    // constexpr bool b = SQUARE_MATRIX_BASE::isMultiplicationPossible<OTHER_MATRIX>();
    // static_assert(b, "ay");

    return result * getInverse();
}



#undef SQUARE_MATRIX_BASE
#undef ENABLE_IF_SQUARED_TEMPLATE_PARAMETERS
#undef SQUARE_MATRIX_BASE_TEMPLATE_PARAMETERS