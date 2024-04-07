#pragma once

class Vec3 {

private:
    float _x, _y, _z;

public:
    Vec3() = default;

    Vec3(float x, float y, float z)
        : _x(x), _y(y), _z(z);

    Vec3 operator+(Vec3 const & v) {
        return Vec3(_x + v._x, _y + v._y, _z + v._z);
    }

    Vec3 operator+=(Vec3 const & v) {
        _x += v._x;
        _y += v._y;
        _z += v._z;
        return *this;
    }

    Vec3 operator*(Vec3 const & v) {
        return Vec3(_x * v._x, _y * v._y, _z * v._z);
    }

    Vec3 operator*=(Vec3 const & v) {
        _x *= v._x;
        _y *= v._y;
        _z *= v._z;
        return *this;
    }
}
