#ifndef VECTOR_HPP
#define VECTOR_HPP

extern "C"
{
  struct Vector2D
  {
    constexpr Vector2D& operator*=(const double rhs)
    {
      x *= rhs;
      y *= rhs;
      return *this;
    }

    constexpr Vector2D Normalized() const
    {
      const double size = std::sqrt((x * x) + (y * y));
      return { x / size, y / size };
    }

    constexpr double Size() const { return std::sqrt((x * x) + (y * y)); }

    constexpr double Distance(const Vector2D& other) const
    {
      return std::sqrt((x - other.x) * (x - other.x) +
                       (y - other.y) * (y - other.y));
    }

    double x;
    double y;
  };
}

#endif // VECTOR_HPP