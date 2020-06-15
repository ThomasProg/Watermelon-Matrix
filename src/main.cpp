#include "baseMatrix.hpp"
#include "matrix.hpp"
#include "baseSquareMatrix.hpp"
#include "squareMatrix.hpp"

#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "vec.hpp"

#include "matrix1x1.hpp"

constexpr float foo()
{
    // Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::identity(); // error, function doesn't exit
    Core::Maths::Matrix<3,1,float> m0 = Core::Maths::Matrix<3,1,float>::zero();

    Core::Maths::Matrix<3,3,float> m1 = Core::Maths::Matrix<3,3,float>::identity();

    Core::Maths::SquareMatrix<3, float> m2 = m1;
    Core::Maths::SquareMatrix<3, float> m2s = {1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f};

    // float det0 = m0.getDeterminant(); // error, function doesn't exit
    float det1 = m1.getDeterminant();

    Core::Maths::Vec3<float> v1 = Core::Maths::Matrix<1, 3, float>();

    Core::Maths::Matrix<1, 3, float> myVec = {};
    myVec.array = {1, 3, 2};

    Core::Maths::Vec<10,float> newVec;
    Core::Maths::Matrix<1, 10, float>& fr = newVec;

    Core::Maths::Matrix<1,3,float> m10 = {1.f,2.f,3.f};

    Core::Maths::Matrix1x1<float> vfg;

    return det1;
}

int main()
{
    constexpr float j = foo();
    std::cout << j << std::endl;

    Core::Maths::Matrix<3,1,float> m10 {1.f,2.f,3.f};
}