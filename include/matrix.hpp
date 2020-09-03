#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "baseMatrix.hpp"
#include "matrixForwardDecl.hpp"

namespace Core::Maths
{
    template<size_t ROWS, size_t COLUMNS, typename ELEM_TYPE>
    class Matrix : public BaseMatrix<Matrix<ROWS, COLUMNS, ELEM_TYPE>, ROWS, COLUMNS, ELEM_TYPE>
    {
    protected:
        using SelfType = Matrix<ROWS, COLUMNS, ELEM_TYPE>;
        using Super = BaseMatrix<Matrix<ROWS, COLUMNS, ELEM_TYPE>, ROWS, COLUMNS, ELEM_TYPE>;

        using ElemType = typename Super::ElemType;

    public:
        union
        {
            ElemType elements[SelfType::getNbElements()];
            std::array<ElemType, SelfType::getNbElements()> array = {};
        };

        __inline constexpr Matrix() noexcept 
            : array()
        {

        }

        // The first argument is used to prevent the confusion with other constructors.
        // TODO : SFINAE should be used.
        template<typename ... ARGS>
        inline constexpr Matrix(ELEM_TYPE&& m, ARGS&& ... args)
            : array({std::forward<ELEM_TYPE>(m), std::forward<ARGS>(args)...})
        {

        }
    };
}

#endif 