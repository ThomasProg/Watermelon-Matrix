#include "matrixBase.hpp"
#include "squareMatrix.hpp"

template class Core::Maths::Matrix<1, 2, float>; // Vec2f
template class Core::Maths::Matrix<1, 3, float>; // Vec3f
template class Core::Maths::Matrix<1, 4, float>; // Vec4f
template class Core::Maths::Matrix<4, 4, float>; // Matrix4x4

template class Core::Maths::SquareMatrix<3,float>;