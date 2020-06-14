#include "matrixBase.hpp"

#include <cassert>

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
inline constexpr size_t Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getNbRows() noexcept
{
    return ROWS;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
inline constexpr size_t Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getNbColumns() noexcept
{
    return COLUMNS;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
inline constexpr size_t Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getNbElements() noexcept
{
    return ROWS * COLUMNS;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
template<typename OTHER_MATRIX, typename>
inline constexpr bool Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::isMultiplicationPossible()
{
    return (getNbColumns() == OTHER_MATRIX::getNbRows()) && (std::is_convertible<ElemType, typename OTHER_MATRIX::ElemType>::value);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator+(const Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& rhs) noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] + rhs.getElements()[i];
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator-(const Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& rhs) noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] - rhs.getElements()[i];
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator*(const Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& rhs) const noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] * rhs.getElements()[i];
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator*(ELEM_TYPE rhs) const noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] * rhs;
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator/(ELEM_TYPE rhs) const noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] / rhs;
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator*=(ELEM_TYPE rhs) noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        getElements()[i] *= rhs;
    }

    return (*this);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator/=(ELEM_TYPE rhs) noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        getElements()[i] /= rhs;
    }

    return (*this);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr ELEM_TYPE const * 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator[](size_t id) const noexcept
{
    assert(id < getNbRows());
    return &this->getElements()[id * getNbColumns()];
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr ELEM_TYPE*  
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator[](size_t id) noexcept
{
    assert(id < getNbRows());
    return &(this->getElements()[id * getNbColumns()]);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
inline constexpr Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>& 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getRow(size_t index) noexcept
{
    // We know that the memory layout of (*this) is something like :
    // 0 - 1 - 2 
    // 3 - 4 - 5
    // 
    // The memory layout of Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE> would be :
    // 0 - 1 - 2 
    // 
    // We notice that the layout is the same at the start; 
    // We can cast safely.
    return * reinterpret_cast<Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>*>((*this)[index]);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
inline constexpr const Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>& 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getRow(size_t index) const noexcept
{
    // We know that the memory layout of (*this) is something like :
    // 0 - 1 - 2 
    // 3 - 4 - 5
    // 
    // The memory layout of Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE> would be :
    // 0 - 1 - 2 
    // 
    // We notice that the layout is the same at the start; 
    // We can cast safely.
    return * reinterpret_cast<const Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>*>((*this)[index]);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr bool 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator==(const Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& rhs) const noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        if (getElements()[i] != rhs.getElements()[i])
            return false; 
    }

    return true;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr bool 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator!=(const Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>& rhs) const noexcept
{
    return !operator==(rhs);
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
template<typename OTHER_MATRIX>
inline constexpr bool Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::isMatrix()
{
    return std::is_base_of<MatrixBase, OTHER_MATRIX>::value;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
constexpr Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> 
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::zero() noexcept
{
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE> returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = static_cast<ELEM_TYPE> (0);
    }

    return returnedMatrix;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE> // template class args
template<typename OTHER_MATRIX, typename> // template function args
constexpr Core::Maths::Matrix<ROWS, OTHER_MATRIX::getNbColumns(), ELEM_TYPE> // return type
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::operator*(const OTHER_MATRIX& rhs) const noexcept
{
    Core::Maths::Matrix<ROWS, rhs.getNbColumns(), ELEM_TYPE> result;

    for (size_t j = 0; j < getNbRows(); j++)
    {
        const size_t jAdded = j * rhs.getNbColumns(); 
        for (size_t i = 0; i < rhs.getNbColumns(); i++)
        {
            ELEM_TYPE& elem = result.getElements()[i + jAdded];
            elem = 0;
            for (size_t k = 0; k < getNbColumns(); k++)
            {
                elem += getElements()[k + jAdded] * rhs.getElements()[k * rhs.getNbColumns() + i];
            }
        }
    }

    return result;
}

template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE> // template class args
template<size_t SELF_ROWS, size_t SELF_COLUMNS, typename> // template function args
constexpr Core::Maths::Matrix<ROWS - 1, COLUMNS - 1, ELEM_TYPE> // return type
    Core::Maths::Matrix<ROWS, COLUMNS, ELEM_TYPE>::getSubMatrix(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
{
    assert(excludedRowIndex < getNbRows() && excludedColumnIndex < getNbColumns());

    Core::Maths::Matrix<ROWS - 1, COLUMNS - 1, ELEM_TYPE> subMatrix;

    // We could compute the sub matrix with only two nested for loops, 
    // but that would mean we would have an "if" running for each loop,
    // and we would loop over unset elements,
    // so we prefer separating the creation of the subMatrix in 4 loops.

    // top left hand corner
    for (size_t i = 0; i < excludedRowIndex; i++)
    {
        for (size_t j = 0; j < excludedColumnIndex; j++)
        {
            subMatrix[i][j] = (*this)[i][j];
        }
    }

    // top right hand corner
    for (size_t i = 0; i < excludedRowIndex; i++)
    {
        for (size_t j = excludedColumnIndex + 1; j < getNbColumns(); j++)
        {
            subMatrix[i][j - 1] = (*this)[i][j];
        }
    }

    // bottom left hand corner
    for (size_t i = excludedRowIndex + 1; i < getNbRows(); i++)
    {
        for (size_t j = 0; j < excludedColumnIndex; j++)
        {
            subMatrix[i - 1][j] = (*this)[i][j];
        }
    }

    // bottom right hand corner
    for (size_t i = excludedRowIndex + 1; i < getNbRows(); i++)
    {
        for (size_t j = excludedColumnIndex + 1; j < getNbColumns(); j++)
        {
            subMatrix[i - 1][j - 1] = (*this)[i][j];
        }
    }

    return subMatrix;   
}

template<size_t RHS_ROWS, size_t RHS_COLUMNS, typename RHS_ELEM_TYPE>
std::ostream& Core::Maths::operator<<(std::ostream& stream, const Core::Maths::Matrix<RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs)
{
    for (size_t i = 0; i < RHS_ROWS; i++)
    {
        for (size_t j = 0; j < RHS_COLUMNS; j++)
        {
            stream << rhs.getElements()[j + i * RHS_COLUMNS] << '\t';
        }
        std::cout << '\n';
    }
    return stream;
}
