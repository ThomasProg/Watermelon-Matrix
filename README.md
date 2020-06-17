# Watermelon-Matrix
C++17 library for vectors and matrices !
This library enables you to do things like :
```cpp
Core::Maths::SquareMatrix<3, float> m1 = Core::Maths::Matrix<3,3,float>::identity();
```
You can also use matrices anywhere in constexpr functions!

Contains : 
- Matrix &lt;ROWS, COLUMNS, T&gt;
- SquareMatrix &lt;SIZE, T&gt;
- Matrix4x4&lt;T&gt;
- Vec&lt;SIZE, T&gt;
- Vec2&lt;T&gt;
- Vec3&lt;T&gt;
- Vec4&lt;T&gt;