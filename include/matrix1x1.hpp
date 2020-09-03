#ifndef _MATRIX1X1_HPP_
#define _MATRIX1X1_HPP_

#include "baseSquareMatrix.hpp"
#include "matrixForwardDecl.hpp"

namespace Core::Maths
{
    template<typename ELEM_TYPE>
    class Matrix<1lu, 1lu, ELEM_TYPE> : public BaseSquareMatrix<Matrix<1lu, 1lu, ELEM_TYPE>, 1lu, ELEM_TYPE>
    {
    protected:
        using SelfType = Matrix<1lu, 1lu, ELEM_TYPE>;
        using Super = BaseSquareMatrix<Matrix<1lu, 1lu, ELEM_TYPE>, 1lu, ELEM_TYPE>;

        using ElemType = typename Super::ElemType;

    public:
        union
        {
            ElemType value;
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