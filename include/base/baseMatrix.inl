#include "baseMatrix.hpp"

#include <cassert>

// Writing all namespaces and template arguments would be long, not maintainable and unreadable.
// We could use "using" or "typedef" to make it shorter, but since it is a .inl file,
// it would be included everywhere, which is not what we want.
// By using macros, we can shorten it, 
// put the definition in one place only (maintainable),
// and we can undef them at the end of the file.
#define BASE_MATRIX_TEMPLATE_PARAMETERS template<class CHILD, size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
#define BASE_MATRIX Core::Maths::BaseMatrix<CHILD, ROWS, COLUMNS, ELEM_TYPE>
#define BASE_MATRIX_EQ typename BASE_MATRIX::EqType

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr size_t BASE_MATRIX::getNbRows() noexcept
{
    return ROWS;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr size_t BASE_MATRIX::getNbColumns() noexcept
{
    return COLUMNS;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr size_t BASE_MATRIX::getNbElements() noexcept
{
    return ROWS * COLUMNS;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr std::array<typename BASE_MATRIX::ElemType, BASE_MATRIX::getNbElements()>& BASE_MATRIX::getElements() noexcept
{
    static_assert(std::is_standard_layout<SelfType>(), "Can't convert a non standard layout : return value would be unspecified.");
    static_assert(std::is_standard_layout<std::array<ElemType, (getNbRows() * getNbColumns())>>(), "Can't convert to a non standard layout : return value would be unspecified.");
    return ((static_cast<CHILD*> (this)) ->array);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr const std::array<typename BASE_MATRIX::ElemType, BASE_MATRIX::getNbElements()>& BASE_MATRIX::getElements() const noexcept
{
    static_assert(std::is_standard_layout<SelfType>(), "Can't convert a non standard layout : return value would be unspecified.");
    static_assert(std::is_standard_layout<std::array<ElemType, (getNbRows() * getNbColumns())>>(), "Can't convert to a non standard layout : return value would be unspecified.");
    return ((static_cast<const CHILD*> (this)) ->array);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
template<typename OTHER_MATRIX, typename>
inline constexpr bool BASE_MATRIX::isMultiplicationPossible()
{
    return (getNbColumns() == OTHER_MATRIX::getNbRows()) && (std::is_convertible<ElemType, typename OTHER_MATRIX::ElemType>::value);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator+(const BASE_MATRIX& rhs) noexcept
{
    BASE_MATRIX_EQ returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] + rhs.getElements()[i];
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator-(const BASE_MATRIX& rhs) noexcept
{
    BASE_MATRIX returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] - rhs.getElements()[i];
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator*(const BASE_MATRIX& rhs) const noexcept
{
    BASE_MATRIX returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] * rhs.getElements()[i];
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator*(ELEM_TYPE rhs) const noexcept
{
    BASE_MATRIX returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] * rhs;
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator/(ELEM_TYPE rhs) const noexcept
{
    BASE_MATRIX_EQ returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = getElements()[i] / rhs;
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX& BASE_MATRIX::operator*=(ELEM_TYPE rhs) noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        getElements()[i] *= rhs;
    }

    return (*this);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX& BASE_MATRIX::operator/=(ELEM_TYPE rhs) noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        getElements()[i] /= rhs;
    }

    return (*this);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr ELEM_TYPE const * BASE_MATRIX::operator[](size_t id) const noexcept
{
    assert(id < getNbRows());
    return &this->getElements()[id * getNbColumns()];
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr ELEM_TYPE* BASE_MATRIX::operator[](size_t id) noexcept
{
    assert(id < getNbRows());
    return &(this->getElements()[id * getNbColumns()]);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::operator-() noexcept
{
    return (-1) * (*this);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>& BASE_MATRIX::getRow(size_t index) noexcept
{
    // We know that the memory layout of (*this) is something like :
    // 0 - 1 - 2 
    // 3 - 4 - 5
    // 
    // The memory layout of Core::Maths::BaseMatrix<1, COLUMNS, ELEM_TYPE> would be :
    // 0 - 1 - 2 
    // 
    // We notice that the layout is the same at the start; 
    // We can cast safely.
    return * reinterpret_cast<Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>*>((*this)[index]);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
inline constexpr const Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>& BASE_MATRIX::getRow(size_t index) const noexcept
{
    // We know that the memory layout of (*this) is something like :
    // 0 - 1 - 2 
    // 3 - 4 - 5
    // 
    // The memory layout of Core::Maths::BaseMatrix<1, COLUMNS, ELEM_TYPE> would be :
    // 0 - 1 - 2 
    // 
    // We notice that the layout is the same at the start; 
    // We can cast safely.
    return * reinterpret_cast<const Core::Maths::Matrix<1, COLUMNS, ELEM_TYPE>*>((*this)[index]);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr bool BASE_MATRIX::operator==(const BASE_MATRIX& rhs) const noexcept
{
    for (size_t i = 0; i < getNbElements(); i++)
    {
        if (getElements()[i] != rhs.getElements()[i])
            return false; 
    }

    return true;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr bool 
    BASE_MATRIX::operator!=(const BASE_MATRIX& rhs) const noexcept
{
    return !operator==(rhs);
}

BASE_MATRIX_TEMPLATE_PARAMETERS
template<typename OTHER_MATRIX>
inline constexpr bool BASE_MATRIX::isMatrix()
{
    return std::is_base_of<BaseMatrix, OTHER_MATRIX>::value;
}

BASE_MATRIX_TEMPLATE_PARAMETERS
constexpr BASE_MATRIX_EQ BASE_MATRIX::zero() noexcept
{
    EqType returnedMatrix;
    for (size_t i = 0; i < getNbElements(); i++)
    {
        returnedMatrix.getElements()[i] = static_cast<ELEM_TYPE> (0);
    }

    return returnedMatrix;
}

BASE_MATRIX_TEMPLATE_PARAMETERS // template class args
template<typename OTHER_MATRIX, typename> // template function args
constexpr Core::Maths::Matrix<ROWS, OTHER_MATRIX::getNbColumns(), ELEM_TYPE> // return type
    BASE_MATRIX::operator*(const OTHER_MATRIX& rhs) const noexcept
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

BASE_MATRIX_TEMPLATE_PARAMETERS // template class args
template<size_t SELF_ROWS, size_t SELF_COLUMNS, typename> // template function args
constexpr Core::Maths::Matrix<ROWS - 1, COLUMNS - 1, ELEM_TYPE> // return type
    BASE_MATRIX::getSubMatrix(size_t excludedRowIndex, size_t excludedColumnIndex) const noexcept
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

template<class RHS_CHILD, size_t RHS_ROWS, size_t RHS_COLUMNS, typename RHS_ELEM_TYPE>
std::ostream& Core::Maths::operator<<(std::ostream& stream, const Core::Maths::BaseMatrix<RHS_CHILD, RHS_ROWS, RHS_COLUMNS, RHS_ELEM_TYPE>& rhs)
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

#undef BASE_MATRIX_EQ
#undef BASE_MATRIX 
#undef BASE_MATRIX_TEMPLATE_PARAMETERS
