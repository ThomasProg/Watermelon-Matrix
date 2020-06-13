#ifndef _MATRIX_4X4_HPP_
#define _MATRIX_4X4_HPP_

#include "squaredMatrix.hpp"

namespace Core::Maths
{
    template<typename ELEM_TYPE>
    class Matrix4x4 : public SquaredMatrix<4lu, ELEM_TYPE>
    {
    protected:
        using MatType = Matrix4x4<ELEM_TYPE>;

    private:


    public:
        Vec3 getXAxis() const;
        Vec3 getYAxis() const;
        Vec3 getZAxis() const;
        Vec3 getTranslationVector() const;

        Vec3 getScale() const;
        Vec3 getSquaredScale() const;

        void normalizeScale();
        Matrix4x4 getInverse() const;

        static Matrix4x4 getProjectionMatrixOnZAxis(const float d);
        static Matrix4x4 CreatePerspectiveProjectionMatrix(int width, int height,float near,float far,float fov);
        static Core::Maths::Matrix4x4 lookAt(const Core::Maths::Vec3& eye, const Core::Maths::Vec3& center, const Core::Maths::Vec3& up);

        static Matrix4x4 CreateScaleMatrix(Vec3 scale);
        static Matrix4x4 CreateTranslationMatrix(Vec3 translation);

        static Matrix4x4 CreateXRotationMatrix(float angleX);
        static Matrix4x4 CreateYRotationMatrix(float angleY);
        static Matrix4x4 CreateZRotationMatrix(float angleZ);

        static Matrix4x4 CreateFixedAngleEulerRotationMatrix(Vec3 angles);

        static Matrix4x4 CreateTRSMatrix(Vec3 scale, Vec3 translation, Vec3 angles);
        static Matrix4x4 CreateTRSMatrix(const Physics::Transform& transform);

        static Matrix4x4 CreateAxisRotationMatrix(const Vec3& axis, float angle); 
    };
}

#include "matrix4x4.inl"

#endif