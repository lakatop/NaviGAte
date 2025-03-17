#ifndef VECTOR_HPP
#define VECTOR_HPP

extern "C"
{
    struct Vector2D
    {
        constexpr Vector2D &operator*=(const double rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        double x;
        double y;
    };
}

#endif // VECTOR_HPP