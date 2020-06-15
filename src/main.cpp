#include "baseMatrix.hpp"
#include "matrix.hpp"
#include "squareMatrixBase.hpp"
#include "squareMatrix.hpp"

constexpr int foo()
{
    Core::Maths::Matrix<3,3,float> m1;
    // for (size_t i = 0; i < m1.getNbElements(); i++)
    //     m1.getElements()[i] = (float)i;

    Core::Maths::Matrix<3,3,float> m2 = m1;

    // m1 = Core::Maths::Matrix<3,3,float>::zero();

    // Core::Maths::SquareMatrix<3, float> m5 = m1;

    return 0;
}

int main()
{
    for (uint iovdrg = 0; iovdrg < 200lu; iovdrg++)
    {
        for (uint iovd2rg = 0; iovd2rg < 2000lu; iovd2rg++)
        {
            for (uint iovd22rg = 0; iovd22rg < 20lu; iovd22rg++)
            {
                constexpr int j = foo();
            }
        }
    }

    // Core::Maths::SquareMatrix<3,float> mx = Core::Maths::SquareMatrix<3,float>::zero();
    // Core::Maths::BaseMatrix<Core::Maths::SquareMatrix<3,float>, 3,3,float> mm = mx;

    
    // Core::Maths::Matrix<3,3,float> mmj = Core::Maths::SquareMatrix<3,float>::zero();
    // Core::Maths::Matrix<3,3,float> mmj2 = Core::Maths::SquareMatrix<3,float>::zero();
    // Core::Maths::SquareMatrix<3,float> m10 = Core::Maths::SquareMatrixBase<Core::Maths::Matrix<3,3,float>, 3,float>(mmj);

    // m1 = Core::Maths::Matrix<3,3,float> (Core::Maths::SquareMatrix<3,float>::zero());
    // std::cout << m1 << std::endl;

    // m1.raiseAsserts();
    // m1.getElements();
}