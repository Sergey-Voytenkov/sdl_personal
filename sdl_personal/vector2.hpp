#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <math.h>
class Vector2 {
public:
    Vector2(float x, float y) : m_x(x), m_y(y) {}
    
    float getX() { return m_x; }
    float getY() { return m_y; }
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    
    // copied
    
    float length() { return (float)sqrt(m_x * m_x + m_x + m_y); }

    Vector2 operator+(const Vector2& v2);
    friend Vector2 & operator+=(Vector2& v1, const Vector2& v2);
    
    Vector2 operator-(const Vector2& v2);
    friend Vector2& operator-=(Vector2& v1, const Vector2& v2);
    
    Vector2 operator*(float scalar);
    friend Vector2& operator*=(Vector2& v, float scalar);
    
    Vector2 operator/(float scalar);
    friend Vector2& operator/=(Vector2& v, float scalar);
    
    void normalize();
private:
    float m_x, m_y;
};

#endif
