#include "matrixBase.hpp"
#include "squareMatrix.hpp"

#define HAS_MEMBER_STRUCT_NAME HASNAME_x_TYPE_int
#define HAS_MEMBER_MEMBER_NAME x
#define HAS_MEMBER_TYPE int
#include "hasMember.hpp"

#define HAS_MEMBER_STRUCT_NAME HASNAME_x_TYPE_char
#define HAS_MEMBER_MEMBER_NAME x
#define HAS_MEMBER_TYPE char
#include "hasMember.hpp"

// #define ASSERT_VALID_MATRIX static_assert(HASNAME_components_TYPE_stdarray<A>::value);

constexpr Core::Maths::Matrix<1,3,float> getRandMat()
{
    Core::Maths::Matrix<1,3,float> ret;

    ret[0][0] = 1;
    ret[0][1] = 1;
    ret[0][2] = 1;

    return ret;
}

constexpr Core::Maths::Matrix<3,2,float> getRandMat2()
{
    Core::Maths::Matrix<3,2,float> ret;

    ret[0][0] = 1;
    ret[1][0] = 2;
    ret[2][0] = 3;

    ret[0][1] = 4;
    ret[1][1] = 5;
    ret[2][1] = 6;

    return ret;
}
#include <vector>
#include "vec.hpp"
#include "vec3.hpp"

class A
{
public:
    char x;
};

int main()
{
    std::cout << HASNAME_x_TYPE_char<A>::value << std::endl;

    {
        constexpr Core::Maths::Matrix<1,3,float> m1 = getRandMat();
        constexpr Core::Maths::Matrix<3,2,float> m2 = getRandMat2();

        constexpr Core::Maths::Matrix<1,2, float> m3 = m1 * m2;

        std::cout << m3 << std::endl;
    }
    std::cout << "=============\n";

    // constexpr Core::Maths::Matrix<1,3,float> m1 = getRandMat();
    // constexpr bool b = Core::Maths::Matrix<1,3,double>::isMultiplicationPossible<Core::Maths::Matrix<3,1,std::vector<int>>>();
    // std::cout << (b ? "yes" : "nop") << std::endl;

    Core::Maths::SquareMatrix<4, float> m = Core::Maths::Matrix<4, 4, float>::zero();
    for (uint i = 0; i < 3; i++)
    {
        m[i][i] = 4;
    }

    Core::Maths::Matrix<4, 1, float> r;
    m.resolveEquation(r);

    m.getElements();

    // std::cout << m << std::endl;
    // std::cout << m.getInverse() << std::endl;
    // std::cout << m.getTranslation() << std::endl;
    // Core::Maths::SquareMatrix<3 - 1, float> subMatrix = (m.getSubMatrix(1lu, 0lu));

    // Core::Maths::SquareMatrix<3, float> m;
    // {
    //     Core::Maths::SquareMatrix<4, float> m1;
    //     for (unsigned int i = 0; i < 16; i++)
    //         m1.elements[i] = i; 

    //     std::cout << m1 << "\nafter transposed : \n" << m1.getTransposed() << std::endl; 
    //     m1.transpose();
    //     std::cout << m1 << std::endl;

    //     std::cout << m1.getSubMatrix(2,2) << std::endl;

    //     // std::cout <<  m1.getInverse() << std::endl;

    //     Core::Maths::Matrix<3, 3, float> mat = (m1.getSubMatrix(1, 0));
    //     Core::Maths::SquareMatrix<4 - 1, float>* subMatrix = reinterpret_cast<Core::Maths::SquareMatrix<4 - 1, float>*> (&mat);

    //     // subMatrix->getAdjoint();
    // }

}




// #include <iostream>
// #include <type_traits>

// template<int T> class MyClass
// {
//     public:
//         MyClass() : myVar{} 
//         {
            
//         }

//         // template<int U = T>
//         // typename std::enable_if<(U == 0)>::type testIf() {
//         //     std::cout << "no" << std::endl;
//         // }

//         // template<int U = T>
//         // typename std::enable_if<!(U == 0)>::type testIf() {
//         //     myVar[0] = 3;
//         //     std::cout << "yes" << std::endl;
//         // }

//         enum class enabler_t {};

//         template<typename U>
//         using EnableIf = typename std::enable_if<U::value, enabler_t>::type;

//         template<int U = T>
//         void testIf(typename std::enable_if<U == 0>::type* = nullptr) {
//             std::cout << "yes " << std::endl;
//             return;
//         }

//         //This function is chosen when a floating point type is passed in
//         template<int U = T>
//         void testIf(typename std::enable_if<U != 0>::type* = nullptr) {
//             std::cout << "nop " << std::endl;
//             return;
//         }

//     public:
//         static const bool isconst = (T == 0);
//         float myVar[T];
// };

// int main()
// {
//     MyClass<0> x;
//     MyClass<2> y;
//     x.testIf();
//     y.testIf();
//     y.myVar[0] = 2.f;
    
//     //std::cout << x.myVar[0] << std::endl;
//     //std::cout << y.myVar[0] << std::endl;
//     return 0;
// }