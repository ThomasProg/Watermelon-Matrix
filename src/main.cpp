#include "baseMatrix.hpp"
#include "matrix.hpp"
#include "baseSquareMatrix.hpp"
#include "squareMatrix.hpp"

#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"

constexpr float foo()
{
    // Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::identity(); // error, function doesn't exit
    Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::zero();

    Core::Maths::Matrix<3,3,float> m1 = Core::Maths::Matrix<3,3,float>::identity();

    Core::Maths::SquareMatrix<3, float> m2 = m1;

    // float det0 = m0.getDeterminant(); // error, function doesn't exit
    float det1 = m1.getDeterminant();

    Core::Maths::Vec3<float> v1 = Core::Maths::Matrix<1, 3, float>();

    Core::Maths::Matrix<1, 3, float> myVec = {};
    myVec.array = {1, 3, 2};


    return det1;
}

int main()
{
    constexpr float j = foo();
    std::cout << j << std::endl;
}