#include "baseMatrix.hpp"
#include "baseSquareMatrix.hpp"

#include "matrix.hpp"
#include "squareMatrix.hpp"

template class Core::Maths::Matrix<1, 2, float>; // Vec2f
template class Core::Maths::Matrix<1, 3, float>; // Vec3f
template class Core::Maths::Matrix<1, 4, float>; // Vec4f
template class Core::Maths::Matrix<4, 4, float>; // Matrix4x4

// template class Core::Maths::SquareMatrixBase<3,float>;

template class Core::Maths::Matrix<3, 3, float>;

#include "vec3.hpp"

// template class Core::Maths::Vec3<float>;