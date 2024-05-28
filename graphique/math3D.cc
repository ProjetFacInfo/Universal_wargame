#include "math3D.hh"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cassert>




Vecteur2f::Vecteur2f(float x, float y)
	: x(x), y(y) {}

float Vecteur2f::longueur() const {
	return sqrtf(x * x + y * y);
}


Vecteur2f & Vecteur2f::normaliser() {
  float lon = longueur();
	assert(lon != 0);

	if (lon > 0.0f) {
		float invLong = 1.0f / lon;
		x *= invLong;
		y *= invLong;
	}

	return *this;
}

Vecteur2f Vecteur2f::operator*(float f) {
    return Vecteur2f(x * f, y * f);
}


Vecteur3f::Vecteur3f(float x, float y, float z)
	: x(x), y(y), z(z) {}

Vecteur3f::Vecteur3f(float f)
	: x(f), y(f), z(f) {}

Vecteur3f::Vecteur3f(const Vecteur3f & v)
	: x(v.x), y(v.y), z(v.z) {}

Vecteur3f::Vecteur3f(const Vecteur4f & v)
	:x(v.x), y(v.y), z(v.z) {}

float Vecteur3f::longueur() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vecteur3f::distance(const Vecteur3f & v) const {
	float delta_x = x - v.x;
	float delta_y = y - v.y;
	float delta_z = z - v.z;
	float distance = sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
	return distance;
}

Vecteur3f Vecteur3f::opposer() const {
  return Vecteur3f(-x, -y, -z);
}

bool Vecteur3f::estZero() const {
	return (x + y + z) == 0.0f;
}

float Vecteur3f::produitScalaire(const Vecteur3f& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vecteur3f Vecteur3f::produitVectoriel(const Vecteur3f & v) const {
	Vecteur3f tmp;
	tmp.x = y * v.z - z * v.y;
  tmp.y = z * v.x - x * v.z;
  tmp.z = x * v.y - y * v.x;

	return tmp;
}

Vecteur3f & Vecteur3f::normaliser() {
  float lon = longueur();
	assert(lon != 0);

	if (lon > 0.0f) {
		float invLong = 1.0f / lon;
		x *= invLong;
		y *= invLong;
		z *= invLong;
	}

	return *this;
}

// rotation utilisant les quaternions
void Vecteur3f::rotation(float angle, const Vecteur3f & v) {
    Quaternion qRotation(angle, v);
    Quaternion qConjugue = qRotation.conjugue();
    Quaternion w = qRotation * (*this) * qConjugue;

    x = w.x;
    y = w.y;
    z = w.z;
}

void Vecteur3f::print() const {
	printf("(%f, %f, %f)", x, y, z);
}

Vecteur3f operator+(const Vecteur3f& g, const Vecteur3f& d) {
	return Vecteur3f(g.x + d.x, g.y + d.y, g.z + d.z);
}

Vecteur3f operator-(const Vecteur3f& g, const Vecteur3f& d) {
	return Vecteur3f(g.x - d.x, g.y - d.y, g.z - d.z);
}

Vecteur3f operator*(const Vecteur3f& g, float f) {
	Vecteur3f tmp(g.x * f, g.y * f, g.z * f);
	return tmp;
}

Vecteur3f operator/(const Vecteur3f& g, float f) {
	return (g.x / f, g.y / f, g.z / f);
}

Vecteur3f & Vecteur3f::operator+=(const Vecteur3f & v) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vecteur3f & Vecteur3f::operator-=(const Vecteur3f & v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vecteur3f & Vecteur3f::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

bool Vecteur3f::operator==(const Vecteur3f & v) {
  return ((x == v.x) && (y == v.y) && (z == v.z));
}

bool Vecteur3f::operator!=(const Vecteur3f & v) {
	return !(*this == v);
}

Vecteur4f::Vecteur4f(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w) {}

Vecteur4f::Vecteur4f(const Vecteur3f& v, float w)
	:x(v.x), y(v.y), z(v.z), w(w) {}

Vecteur4f::Vecteur4f(const Vecteur4f & v)
	:x(v.x), y(v.y), z(v.z), w(v.w) {}

Vecteur3f Vecteur4f::vec4fEnVec3f() const {
		return Vecteur3f(x, y, z);
}

float Vecteur4f::longueur() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vecteur4f & Vecteur4f::normaliser() {
  float lon = longueur();
	assert(lon != 0);

	if (lon > 0.0f) {
		float invLong = 1.0f / lon;
		x *= invLong;
		y *= invLong;
		z *= invLong;
		w *= invLong;
	}

	return *this;
}


float Vecteur4f::produitScalaire(const Vecteur4f& v) const {
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vecteur4f operator+(const Vecteur4f & g, const Vecteur4f & d) {
	return Vecteur4f(g.x + d.x, g.y + d.y, g.z + d.z, g.w + d.w);
}

Vecteur4f operator-(const Vecteur4f & g, const Vecteur4f & d) {
	return Vecteur4f(g.x - d.x, g.y - d.y, g.z - d.z, g.w - d.w);
}

Vecteur4f operator*(const Vecteur4f & g, float f) {
	return Vecteur4f(g.x * f, g.y * f, g.z * f, g.w * f);
}

Vecteur4f operator/(const Vecteur4f & g, float f) {
	return Vecteur4f(g.x / f, g.y / f, g.z / f, g.w / f);
}

Vecteur4f & Vecteur4f::operator+=(const Vecteur4f & v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

Vecteur4f & Vecteur4f::operator-=(const Vecteur4f & v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

Vecteur4f & Vecteur4f::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

bool Vecteur4f::operator==(const Vecteur4f& v) {
	return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w));
}

bool Vecteur4f::operator!=(const Vecteur4f & v) {
	return !(*this == v);
}



Quaternion::Quaternion(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(float Angle, const Vecteur3f& V) {
	float demiAngleEnRadian = degreeEnRadian(Angle/2);

	float sinDemiAngle = sinf(demiAngleEnRadian);
	float cosDemiAngle = cosf(demiAngleEnRadian);

	x = V.x * sinDemiAngle;
	y = V.y * sinDemiAngle;
	z = V.z * sinDemiAngle;
	w = cosDemiAngle;
}

Quaternion::Quaternion(const Quaternion & q)
	:x(q.x), y(q.y), z(q.z), w(q.w) {}



float Quaternion::longueur() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vecteur3f Quaternion::enDegree() {
	float x = atan2(x * z + y * w, x * w - y * z);
	float y = acos(-x * x - y * y - z * z - w * w);
	float z = atan2(x * z - y * w, x * w + y * z);

	x = radianEnDegree(x);
	y = radianEnDegree(y);
	z = radianEnDegree(z);

	return Vecteur3f(x,y,z);
}

Quaternion Quaternion::conjugue() const {
	return Quaternion(-x, -y, -z, w);
}

Quaternion & Quaternion::normaliser() {
  float lon = longueur();
	assert(lon != 0);

	if (lon > 0.0f) {
		float invLong = 1.0f / lon;
		x *= invLong;
		y *= invLong;
		z *= invLong;
		w *= invLong;
	}

	return *this;
}

Quaternion operator*(const Quaternion & g, const Quaternion & d) {
	float w = (g.w * d.w) - (g.x * d.x) - (g.y * d.y) - (g.z * d.z);
	float x = (g.x * d.w) + (g.w * d.x) + (g.y * d.z) - (g.z * d.y);
	float y = (g.y * d.w) + (g.w * d.y) + (g.z * d.x) - (g.x * d.z);
	float z = (g.z * d.w) + (g.w * d.z) + (g.x * d.y) - (g.y * d.x);

	return Quaternion(x, y, z, w);
}

Quaternion operator*(const Quaternion & q, const Vecteur3f & v) {
	float w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	float x =   (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	float y =   (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	float z =   (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	return Quaternion(x, y, z, w);
}



Matrice3f::Matrice3f(
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22) {
	m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
	m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
	m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
}

Matrice3f::Matrice3f(const Matrice3f & o) {
	m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2];
	m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2];
	m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2];
}

Matrice3f::Matrice3f(const Matrice4f & o) {
	m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2];
	m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2];
	m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2];
}

void Matrice3f::identite() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
}

Matrice3f Matrice3f::transposer() const {
	Matrice3f r;

	for (unsigned int i = 0 ; i < 3 ; i++) {
		for (unsigned int j = 0 ; j < 3 ; j++) {
			r.m[i][j] = m[j][i];
		}
	}
	return r;
}

Vecteur3f Matrice3f::operator*(const Vecteur3f & v) const {
	Vecteur3f r;

	r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;

	return r;
}


Matrice3f Matrice3f::operator*(const Matrice3f & o) const {
	Matrice3f r;
	for (unsigned int i = 0 ; i < 3 ; i++) {
		for (unsigned int j = 0 ; j < 3 ; j++) {
			r.m[i][j] = m[i][0] * o.m[0][j] + m[i][1] * o.m[1][j] + m[i][2] * o.m[2][j];
		}
	}

	return r;
}

Matrice4f::operator const float*() const {
	return &(m[0][0]);
}

Matrice4f::Matrice4f() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrice4f::Matrice4f(float f) {
	m[0][0] = f; m[0][1] = f; m[0][2] = f; m[0][3] = f;
	m[1][0] = f; m[1][1] = f; m[1][2] = f; m[1][3] = f;
	m[2][0] = f; m[2][1] = f; m[2][2] = f; m[2][3] = f;
	m[3][0] = f; m[3][1] = f; m[3][2] = f; m[3][3] = f;
}

Matrice4f::Matrice4f(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33
		) {
	m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
	m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
	m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
	m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
}

Matrice4f::Matrice4f(const Matrice3f & o) {
	m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2]; m[0][3] = 0.0f;
	m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2]; m[1][3] = 0.0f;
	m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2]; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrice4f::Matrice4f(const Matrice4f & o) {
	m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2]; m[0][3] = o.m[0][3];
	m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2]; m[1][3] = o.m[1][3];
	m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2]; m[2][3] = o.m[2][3];
	m[3][0] = o.m[3][0]; m[3][1] = o.m[3][1]; m[3][2] = o.m[3][2]; m[3][3] = o.m[3][3];
}

Matrice4f::Matrice4f(const aiMatrix3x3 & am) {
	m[0][0] = am.a1; m[0][1] = am.a2; m[0][2] = am.a3; m[0][3] = 0.0f;
	m[1][0] = am.b1; m[1][1] = am.b2; m[1][2] = am.b3; m[1][3] = 0.0f;
	m[2][0] = am.c1; m[2][1] = am.c2; m[2][2] = am.c3; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrice4f::Matrice4f(const aiMatrix4x4 & am) {
	m[0][0] = am.a1; m[0][1] = am.a2; m[0][2] = am.a3; m[0][3] = am.a4;
	m[1][0] = am.b1; m[1][1] = am.b2; m[1][2] = am.b3; m[1][3] = am.b4;
	m[2][0] = am.c1; m[2][1] = am.c2; m[2][2] = am.c3; m[2][3] = am.c4;
	m[3][0] = am.d1; m[3][1] = am.d2; m[3][2] = am.d3; m[3][3] = am.d4;
}


void Matrice4f::identite() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrice4f Matrice4f::transposer() const {
	Matrice4f n;

	for (unsigned int i = 0 ; i < 4 ; i++) {
		for (unsigned int j = 0 ; j < 4 ; j++) {
			n.m[i][j] = m[j][i];
		}
	}

	return n;
}

float Matrice4f::determinant() const {
	return (
			m[0][0]*m[1][1]*m[2][2]*m[3][3] - m[0][0]*m[1][1]*m[2][3]*m[3][2]
		+ m[0][0]*m[1][2]*m[2][3]*m[3][1] - m[0][0]*m[1][2]*m[2][1]*m[3][3]
		+ m[0][0]*m[1][3]*m[2][1]*m[3][2] - m[0][0]*m[1][3]*m[2][2]*m[3][1]
		- m[0][1]*m[1][2]*m[2][3]*m[3][0] + m[0][1]*m[1][2]*m[2][0]*m[3][3]
		- m[0][1]*m[1][3]*m[2][0]*m[3][2] + m[0][1]*m[1][3]*m[2][2]*m[3][0]
		- m[0][1]*m[1][0]*m[2][2]*m[3][3] + m[0][1]*m[1][0]*m[2][3]*m[3][2]
		+ m[0][2]*m[1][3]*m[2][0]*m[3][1] - m[0][2]*m[1][3]*m[2][1]*m[3][0]
		+ m[0][2]*m[1][0]*m[2][1]*m[3][3] - m[0][2]*m[1][0]*m[2][3]*m[3][1]
		+ m[0][2]*m[1][1]*m[2][3]*m[3][0] - m[0][2]*m[1][1]*m[2][0]*m[3][3]
		- m[0][3]*m[1][0]*m[2][1]*m[3][2] + m[0][3]*m[1][0]*m[2][2]*m[3][1]
		- m[0][3]*m[1][1]*m[2][2]*m[3][0] + m[0][3]*m[1][1]*m[2][0]*m[3][2]
		- m[0][3]*m[1][2]*m[2][0]*m[3][1] + m[0][3]*m[1][2]*m[2][1]*m[3][0] );
}

Matrice4f Matrice4f::inverse() const {
        float det = determinant();

        if(det == 0.0f) {
            assert(0);
            return *this;
        }

        float detInv = 1.0f / det;

        Matrice4f n;
        n.m[0][0] = detInv  * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
															+ m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3])
															+ m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));

        n.m[0][1] = -detInv * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
															+ m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3])
															+ m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));

        n.m[0][2] = detInv  * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2])
															+ m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3])
															+ m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));

        n.m[0][3] = -detInv * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
															+ m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3])
															+ m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));

        n.m[1][0] = -detInv * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
															+ m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3])
															+ m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));

        n.m[1][1] = detInv  * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
															+ m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3])
															+ m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));

        n.m[1][2] = -detInv * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2])
															+ m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3])
															+ m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));

        n.m[1][3] = detInv  * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
															+ m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3])
															+ m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));

        n.m[2][0] = detInv  * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1])
															+ m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3])
															+ m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

        n.m[2][1] = -detInv * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1])
															+ m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3])
															+ m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

        n.m[2][2] = detInv  * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1])
															+ m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3])
															+ m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));

        n.m[2][3] = -detInv * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1])
															+ m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3])
															+ m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));

        n.m[3][0] = -detInv * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
															+ m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2])
															+ m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

        n.m[3][1] = detInv  * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
															+ m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2])
															+ m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

        n.m[3][2] = -detInv * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1])
															+ m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2])
															+ m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));

        n.m[3][3] = detInv  * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
															+ m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2])
															+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));

        return n;
}

void Matrice4f::setZero() {
	memset(m, 0, sizeof(m));
}

Matrice4f Matrice4f::operator*(const Matrice4f & o) const {
	Matrice4f n;

	for (unsigned int i = 0 ; i < 4 ; i++) {
		for (unsigned int j = 0 ; j < 4 ; j++) {
			n.m[i][j] = m[i][0] * o.m[0][j]
								+ m[i][1] * o.m[1][j]
								+ m[i][2] * o.m[2][j]
								+ m[i][3] * o.m[3][j];
		}
	}

	return n;
}

Vecteur4f Matrice4f::operator*(const Vecteur4f & v) const {
	Vecteur4f n;

	n.x = m[0][0]* v.x + m[0][1]* v.y + m[0][2]* v.z + m[0][3]* v.w;
	n.y = m[1][0]* v.x + m[1][1]* v.y + m[1][2]* v.z + m[1][3]* v.w;
	n.z = m[2][0]* v.x + m[2][1]* v.y + m[2][2]* v.z + m[2][3]* v.w;
	n.w = m[3][0]* v.x + m[3][1]* v.y + m[3][2]* v.z + m[3][3]* v.w;

	return n;
}

void Matrice4f::scaleTransform(float x, float y, float z) {
    m[0][0] = x;      m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;   m[1][1] = y;      m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = z;      m[2][3] = 0.0f;
    m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Matrice4f::scaleTransform(float s) {
    scaleTransform(s, s, s);
}

// Rotatation par angle d'Euleur
void Matrice4f::rotationTransform(float angle, float x, float y, float z) {
    float c = cos(angle);
    float s = sin(angle);

    m[0][0] = (1 - c) * x * x + c;
    m[0][1] = (1 - c) * x * y - s * z;
    m[0][2] = (1 - c) * x * z + s * y;
    m[0][3] = 0.0f;

    m[1][0] = (1 - c) * x * y + s * z;
    m[1][1] = (1 - c) * y * y + c;
    m[1][2] = (1 - c) * y * z - s * x;
    m[1][3] = 0.0f;

    m[2][0] = (1 - c) * x * z - s * y;
    m[2][1] = (1 - c) * y * z + s * x;
    m[2][2] = (1 - c) * z * z + c;
    m[2][3] = 0.0f;

    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrice4f::rotationTransform(float x, float y, float z) {
    Matrice4f rx, ry, rz;

    rx.rotationX(degreeEnRadian(x));
    ry.rotationY(degreeEnRadian(y));
    rz.rotationZ(degreeEnRadian(z));

    *this = rz * ry * rx;
}

void Matrice4f::rotationTransformZYX(float x, float y, float z) {
    Matrice4f rx, ry, rz;

    rx.rotationX(degreeEnRadian(x));
    ry.rotationY(degreeEnRadian(y));
    rz.rotationZ(degreeEnRadian(z));

    *this = rx * ry * rz;
}

void Matrice4f::rotationTransform(const Vecteur3f  & r) {
    rotationTransform(r.x, r.y, r.z);
}


void Matrice4f::rotationX(float x) {
    m[0][0] = 1.0f; m[0][1] = 0.0f   ;  m[0][2] = 0.0f    ; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = cosf(x);  m[1][2] = sinf(x);  m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = -sinf(x); m[2][2] = cosf(x) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f   ;  m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void Matrice4f::rotationY(float y) {
    m[0][0] = cosf(y); m[0][1] = 0.0f; m[0][2] = -sinf(y); m[0][3] = 0.0f;
    m[1][0] = 0.0f   ; m[1][1] = 1.0f; m[1][2] = 0.0f    ; m[1][3] = 0.0f;
    m[2][0] = sinf(y); m[2][1] = 0.0f; m[2][2] = cosf(y) ; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ; m[3][1] = 0.0f; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
}


void Matrice4f::rotationZ(float z) {
    m[0][0] = cosf(z);  m[0][1] = sinf(z);  m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = -sinf(z); m[1][1] = cosf(z) ; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f   ;  m[2][1] = 0.0f    ; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f   ;  m[3][1] = 0.0f    ; m[3][2] = 0.0f; m[3][3] = 1.0f;
}


// Rotatation par quaternion
void Matrice4f::rotationTransform(const Quaternion  & q) {
    float yy2 = 2.0f * q.y * q.y;
    float xy2 = 2.0f * q.x * q.y;
    float xz2 = 2.0f * q.x * q.z;
    float yz2 = 2.0f * q.y * q.z;
    float zz2 = 2.0f * q.z * q.z;
    float wz2 = 2.0f * q.w * q.z;
    float wy2 = 2.0f * q.w * q.y;
    float wx2 = 2.0f * q.w * q.x;
    float xx2 = 2.0f * q.x * q.x;

    m[0][0] = - yy2 - zz2 + 1.0f; m[0][1] = xy2 + wz2; m[0][2] = xz2 - wy2; m[0][3] = 0.0f;
    m[1][0] = xy2 - wz2; m[1][1] = - xx2 - zz2 + 1.0f; m[1][2] = yz2 + wx2; m[1][3] = 0.0f;
    m[2][0] = xz2 + wy2; m[2][1] = yz2 - wx2; m[2][2] = - xx2 - yy2 + 1.0f; m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = 0; m[3][3] = 1.0f;
}


void Matrice4f::translationTransform(float x, float y, float z) {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}


void Matrice4f::translationTransform(const Vecteur3f & pos) {
    translationTransform(pos.x, pos.y, pos.z);
}

void Matrice4f::cameraTransform(const Vecteur3f & cible, const Vecteur3f & up) {
    Vecteur3f N = cible;
    N.normaliser();

    Vecteur3f upNorm = up;
    upNorm.normaliser();

    Vecteur3f U;
    U = upNorm.produitVectoriel(N);
    U.normaliser();

    Vecteur3f V = N.produitVectoriel(U);

    m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
    m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
    m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}


void Matrice4f::cameraTransform(const Vecteur3f & pos, const Vecteur3f & cible, const Vecteur3f & up) {
    Matrice4f cameraTranslation;
    cameraTranslation.translationTransform(-pos.x, -pos.y, -pos.z);

    Matrice4f cameraRotateTrans;
    cameraRotateTrans.cameraTransform(cible, up);

    *this = cameraRotateTrans * cameraTranslation;
}

void Matrice4f::persProjTransform(const PersProjInfo & p) {
    float ar         = p.hauteur / p.largeur;
    float zEcart     = p.zProche - p.zLoin;
    float demiTanCDV = tanf(degreeEnRadian(p.CDV / 2.0f));

    m[0][0] = 1 / demiTanCDV;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 1.0f / (demiTanCDV * ar);
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (-p.zProche - p.zLoin) / zEcart ;
    m[2][3] = (2.0f * p.zLoin * p.zProche) / zEcart;

    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 1.0f; m[3][3] = 0.0f;

}

void Matrice4f::orthoProjTransform(const OrthoProjInfo & p) {

    m[0][0] = 2.0f / (p.droite - p.gauche);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(p.droite + p.gauche) / (p.droite - p.gauche);

    m[1][0] = 0.0f;
    m[1][1] = 2.0f / (p.haut - p.bas);
    m[1][2] = 0.0f;
    m[1][3] = -(p.haut + p.bas) / (p.haut - p.bas);

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 2.0f / (p.zLoin - p.zProche);
    m[2][3] = -(p.zLoin + p.zProche) / (p.zLoin - p.zProche);

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;

}


float degreeEnRadian(float f) {
    return (float)(f * M_PI / 180.0f);
}

float radianEnDegree(float f) {
    return (float)(f * 180.0f / M_PI);
}

float floattantAleatoire() {
    return (rand() / (float)RAND_MAX);
}
float plageFloattantAleatoire(float deb, float fin) {
    return floattantAleatoire() * (fin - deb) + deb;
}

float baryCentriqueCoord(const Vecteur3f & p1, const Vecteur3f & p2, const Vecteur3f & p3, const Vecteur2f & pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
