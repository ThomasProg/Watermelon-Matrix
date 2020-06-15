#include "baseMatrix.hpp"
#include "matrix.hpp"
#include "baseSquareMatrix.hpp"
#include "squareMatrix.hpp"

constexpr float foo()
{
    // Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::identity(); // error, function doesn't exit
    Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::zero();

    Core::Maths::Matrix<3,3,float> m1 = Core::Maths::Matrix<3,3,float>::identity();

    Core::Maths::SquareMatrix<3, float> m2 = m1;

    // float det0 = m0.getDeterminant(); // error, function doesn't exit
    float det1 = m1.getDeterminant();

    return det1;
}

int main()
{
    constexpr float j = foo();
    std::cout << j << std::endl;
}