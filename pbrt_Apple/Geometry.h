#pragma once
#include "inc.h"
#ifdef __SSE_ACC
#include <xmmintrin.h>
#endif
#include <math.h>
class Vector
{
public:
	__m128 v_m;
	float x, y, z;
	Vector() { v_m =_mm_set_ps1(0.f); }
	Vector(const Vector& v) { v_m = v.v_m; }
	Vector(const __m128& v) { v_m = v; }
	Vector(float x, float y, float z)
	{
		v_m = _mm_set_ps(0.f, z, y, x);
	}
	~Vector() {}

	Vector &operator=(const Vector &v) {
		v_m = v.v_m;
		return *this;
	}

	Vector operator+(const Vector &v) const {
		return Vector(_mm_add_ps(v_m, v.v_m));
	}

	Vector& operator+=(const Vector &v) {
		v_m = _mm_add_ps(v_m, v.v_m);
		return *this;
	}

	Vector operator-(const Vector &v) const {
		return Vector(_mm_sub_ps(v_m, v.v_m));
	}

	Vector& operator-=(const Vector &v) {
		v_m = _mm_sub_ps(v_m, v.v_m);
		return *this;
	}
	Vector operator*(float f) const { 
		__m128 m_f = _mm_set_ps1(f);
		return Vector(_mm_mul_ps(v_m,m_f)); 
	}

	Vector &operator*=(float f) {
		__m128 m_f = _mm_set_ps1(f);
		v_m = _mm_mul_ps(v_m, m_f);
		return *this;
	}
	Vector operator/(float f) const {
		__m128 m_f = _mm_set_ps1(1/f);
		return Vector(_mm_mul_ps(v_m, m_f));
	}

	Vector &operator/=(float f) {
		__m128 m_f = _mm_set_ps1(1/f);
		v_m = _mm_mul_ps(v_m, m_f);
		return *this;
	}
	Vector operator-() const { return Vector(-x, -y, -z); }
	float operator[](int i) const {
		return (&x)[i];
	}

	float &operator[](int i) {
		return (&x)[i];
	}
	float LengthSquared() const { return x*x + y*y + z*z; }
	float Length() const { return sqrtf(LengthSquared()); }
	

	bool operator==(const Vector &v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	bool operator!=(const Vector &v) const {
		return x != v.x || y != v.y || z != v.z;
	}
};

