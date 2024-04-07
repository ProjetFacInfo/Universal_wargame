#pragma once

class Vec2 {

private:
    float _x, _y;

public:
    Vec2()
        : _x(0.0f), _y(0.0) {}

    Vec2(float x, float y)
        : _x(x), _y(y) {}

    Vec2 operator+(Vec2 const & v) {
        return Vec2(_x + v._x, _y + v._y);
    }

    Vec2 operator+=(Vec2 const & v) {
        _x += v._x;
        _y += v._y;
        return *this;
    }

    Vec2 operator*(Vec2 const & v) {
        return Vec2(_x * v._x, _y * v._y);
    }

    Vec2 operator*=(Vec2 const & v) {
        _x *= v._x;
        _y *= v._y;
        return *this;
    }
}
