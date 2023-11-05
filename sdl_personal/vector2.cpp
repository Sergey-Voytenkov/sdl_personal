#include "vector2.hpp"

Vector2 Vector2::operator+(const Vector2& v2) {
    return Vector2(m_x + v2.m_x, m_y + v2.m_y);
};

Vector2& operator+=(Vector2& v1, const Vector2& v2) {
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;
    
    return v1;
};

Vector2 Vector2::operator-(const Vector2& v2) {
    return Vector2(m_x - v2.m_x, m_y - v2.m_y);
};

Vector2& operator-=(Vector2& v1, const Vector2& v2) {
    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;
    
    return v1;
}

Vector2 Vector2::operator*(float scalar) {
    return Vector2(m_x * scalar, m_y * scalar);
};

Vector2& operator*=(Vector2& v, float scalar) {
    v.m_x *= scalar;
    v.m_y *= scalar;
    
    return v;
};

Vector2 Vector2::operator/(float scalar) {
    return Vector2(m_x / scalar, m_y / scalar);
};

Vector2& operator/=(Vector2& v, float scalar) {
    v.m_x /= scalar;
    v.m_y /= scalar;
    
    return v;
};

void Vector2::normalize() {
    float l = length();
    
    if (l > 0)
        (*this) *= 1 / l;
}
