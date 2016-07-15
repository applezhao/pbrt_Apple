#pragma once
#include "inc.h"
#ifdef __SSE_ACC
#include <xmmintrin.h>
#endif
#include <math.h>
#include <algorithm>
namespace PBRT {
	namespace BASE {

		enum axis {
			X=0,
			Y,
			Z
		};

		struct float4
		{
			float x;
			float y;
			float z;
			float w;

			float4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w)
			{}
		};
		union float4_sse
		{
			__m128 mm;
			float4 ff;

			float4_sse() {}
			explicit float4_sse(__m128 mm) :mm(mm) {}
			explicit float4_sse(float4 ff) :ff(ff) {}
		};

		class Vector
		{
		public:
			float4_sse value;
			Vector() { value.mm = _mm_set_ps1(0.f); }
			Vector(const Vector& v) { value.mm = v.value.mm; }
			Vector(const __m128& v) { value.mm = v; }
			Vector(float x, float y, float z)
			{
				value.ff = float4(x, y, z, 0);
			}
			~Vector() {}

			Vector &operator=(const Vector &v) {
				value.mm = v.value.mm;
				return *this;
			}

			Vector operator+(const Vector &v) const {
				return Vector(_mm_add_ps(value.mm, v.value.mm));
			}

			Vector& operator+=(const Vector &v) {
				value.mm = _mm_add_ps(value.mm, v.value.mm);
				return *this;
			}

			Vector operator-(const Vector &v) const {
				return Vector(_mm_sub_ps(value.mm, v.value.mm));
			}

			Vector& operator-=(const Vector &v) {
				value.mm = _mm_sub_ps(value.mm, v.value.mm);
				return *this;
			}
			/*Vector operator*(float f) const {
				__m128 m_f = _mm_set_ps1(f);
				return Vector(_mm_mul_ps(value.mm, m_f));
			}*/

			friend Vector operator*(float f, const Vector& v);

			friend Vector operator*(const Vector& v, float f);

			friend float Dot(const Vector& v1, const Vector& v2);

			friend float Dot(const Vector& v1, const Normal& v2);

			friend float Dot(const Normal& v1, const Vector& v2);

			friend Vector Cross(const Vector& v1, const Vector& v2);

			friend Vector Cross(const Vector& v1, const Normal& v2);

			friend Vector Cross(const Normal& v1, const Vector& v2);

			friend Vector Normalize(const Vector& v);

			Vector &operator*=(float f) {
				__m128 m_f = _mm_set_ps1(f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Vector operator/(float f) const {
				__m128 m_f = _mm_set_ps1(1 / f);
				return Vector(_mm_mul_ps(value.mm, m_f));
			}

			Vector &operator/=(float f) {
				__m128 m_f = _mm_set_ps1(1 / f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Vector operator-() const { return Vector(-value.ff.x, -value.ff.y, -value.ff.z); }
			float operator[](int i) const {
				return (&value.ff.x)[i];
			}

			float &operator[](int i) {
				return (&value.ff.x)[i];
			}
			float LengthSquared() const { return value.ff.x*value.ff.x + value.ff.y*value.ff.y + value.ff.z*value.ff.z; }
			float Length() const { return sqrtf(LengthSquared()); }


			bool operator==(const Vector &v) const {
				return value.ff.x == v.value.ff.x && value.ff.y == v.value.ff.y && value.ff.z == v.value.ff.z;
			}
			bool operator!=(const Vector &v) const {
				return value.ff.x != v.value.ff.x || value.ff.y != v.value.ff.y || value.ff.z != v.value.ff.z;;
			}
		};

		class Point
		{
		public:
			float4_sse value;
			Point() { value.mm = _mm_set_ps1(0.f); value.ff.w = 1; }
			Point(const Point& v) { value.mm = v.value.mm; }
			Point(const __m128& v) { value.mm = v; }
			Point(float x, float y, float z)
			{
				value.ff = float4(x, y, z, 1);
			}
			~Point() {}

			Point &operator=(const Point &v) {
				value.mm = v.value.mm;
				return *this;
			}

			Point operator+(const Point &v) const {
				return Point(_mm_add_ps(value.mm, v.value.mm));
			}

			Point operator+(const Vector &v) const {
				return Point(_mm_add_ps(value.mm, v.value.mm));
			}

			Point& operator+=(const Point &v) {
				value.mm = _mm_add_ps(value.mm, v.value.mm);
				return *this;
			}

			Point &operator+=(const Vector &v) {
				value.mm = _mm_add_ps(value.mm, v.value.mm);
				return *this;
			}

			Vector operator-(const Point &v) const {
				return Vector(_mm_sub_ps(value.mm, v.value.mm));
			}

			Point operator-(const Vector &v) const {
				return Point(_mm_sub_ps(value.mm, v.value.mm));
			}

			Point& operator-=(const Vector &v) {
				value.mm = _mm_sub_ps(value.mm, v.value.mm);
				return *this;
			}

			Point operator*(float f) const {
				__m128 m_f = _mm_set_ps1(f);
				return Point(_mm_mul_ps(value.mm, m_f));
			}

			Point &operator*=(float f) {
				__m128 m_f = _mm_set_ps1(f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Point operator/(float f) const {
				__m128 m_f = _mm_set_ps1(1 / f);
				return Point(_mm_mul_ps(value.mm, m_f));
			}

			Point &operator/=(float f) {
				__m128 m_f = _mm_set_ps1(1 / f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Point operator-() const { return Point(-value.ff.x, -value.ff.y, -value.ff.z); }
			float operator[](int i) const {
				return (&value.ff.x)[i];
			}

			float &operator[](int i) {
				return (&value.ff.x)[i];
			}

			bool operator==(const Point &v) const {
				return value.ff.x == v.value.ff.x && value.ff.y == v.value.ff.y && value.ff.z == v.value.ff.z;
			}
			bool operator!=(const Point &v) const {
				return value.ff.x != v.value.ff.x || value.ff.y != v.value.ff.y || value.ff.z != v.value.ff.z;;
			}
		};

		class Normal
		{
		public:
			float4_sse value;
			Normal() { value.mm = _mm_set_ps1(0.f); }
			Normal(const Normal& v) { value.mm = v.value.mm; }
			Normal(const __m128& v) { value.mm = v; }
			Normal(float x, float y, float z)
			{
				value.ff = float4(x, y, z, 0);
			}
			explicit Normal(const Vector& v) { value.mm = v.value.mm; }
			~Normal() {}

			Normal &operator=(const Normal &v) {
				value.mm = v.value.mm;
				return *this;
			}

			Normal operator+(const Normal &v) const {
				return Normal(_mm_add_ps(value.mm, v.value.mm));
			}

			Normal& operator+=(const Normal &v) {
				value.mm = _mm_add_ps(value.mm, v.value.mm);
				return *this;
			}

			Vector operator-(const Normal &v) const {
				return Vector(_mm_sub_ps(value.mm, v.value.mm));
			}

			Normal& operator-=(const Normal &v) {
				value.mm = _mm_sub_ps(value.mm, v.value.mm);
				return *this;
			}

			Normal operator*(float f) const {
				__m128 m_f = _mm_set_ps1(f);
				return Normal(_mm_mul_ps(value.mm, m_f));
			}

			Normal &operator*=(float f) {
				__m128 m_f = _mm_set_ps1(f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Normal operator/(float f) const {
				__m128 m_f = _mm_set_ps1(1 / f);
				return Normal(_mm_mul_ps(value.mm, m_f));
			}

			Normal &operator/=(float f) {
				__m128 m_f = _mm_set_ps1(1 / f);
				value.mm = _mm_mul_ps(value.mm, m_f);
				return *this;
			}
			Normal operator-() const { return Normal(-value.ff.x, -value.ff.y, -value.ff.z); }
			float operator[](int i) const {
				return (&value.ff.x)[i];
			}

			float &operator[](int i) {
				return (&value.ff.x)[i];
			}

			float LengthSquared() const { return value.ff.x*value.ff.x + value.ff.y*value.ff.y + value.ff.z*value.ff.z; }
			float Length() const { return sqrtf(LengthSquared()); }

			bool operator==(const Normal &v) const {
				return value.ff.x == v.value.ff.x && value.ff.y == v.value.ff.y && value.ff.z == v.value.ff.z;
			}
			bool operator!=(const Normal &v) const {
				return value.ff.x != v.value.ff.x || value.ff.y != v.value.ff.y || value.ff.z != v.value.ff.z;;
			}

			friend Normal Normalize(const Normal& v) {
				return v / v.Length();
			}
		};

		class Ray {
		public:
			Point o;
			Vector d;
			mutable float mint, maxt;
			float time;
			int depth;

			Ray() : mint(0), maxt(INFINITY), time(0), depth(0){}

			Ray(const Point& o, const Vector& d, float start, float end = INFINITY, float time = 0, float depth = 0)
				:o(o), d(d), mint(start), maxt(end), time(time), depth(depth) {}

			Ray(const Point& o, const Vector& d, const Ray& parent, float start, float end = INFINITY)
				:o(o), d(d), mint(start), maxt(end), time(parent.time), depth(parent.depth+1) {}

			Point operator()(float t) const { return o + d*t; }
		};

		class RayDifferential : public Ray {
		public:
			Point rxOrigin, ryOrigin;
			Vector rxDirection, ryDirection;
			bool hasDifferential;

			RayDifferential() { hasDifferential = false; }

			RayDifferential(const Ray& r) :Ray(r) {
				hasDifferential = false;
			}

			RayDifferential(const Point& o, const Vector& d, float start, float end = INFINITY, float time = 0, float depth = 0)
				:Ray(o,d,start,end,time,depth){
				hasDifferential = false;
			}

			RayDifferential(const Point& o, const Vector& d, const Ray& parent, float start, float end = INFINITY)
				:Ray(o, d, parent, start, end) {
				hasDifferential = false;
			}

			void setDifferential(const Point& rxOrigin, const Point& ryOrigin, const Vector& rxDirection, const Vector& ryDirection)
			{
				hasDifferential = true;
				this->rxOrigin = rxOrigin;
				this->ryOrigin = ryOrigin;
				this->rxDirection = rxDirection;
				this->ryDirection = ryDirection;
			}

			void ScaleDifferential(float s)
			{
				rxOrigin = o + (rxOrigin - o)*s;
				ryOrigin = o + (ryOrigin - o)*s;
				rxDirection = d + (rxDirection - d)*s;
				ryDirection = d + (ryDirection - d)*s;
			}
		};

		class BBox {
		public:
			Point pMin, pMax;

			BBox() { pMin = Point(INFINITY, INFINITY, INFINITY); pMax = Point(-INFINITY, -INFINITY, -INFINITY);}
			BBox(const Point& p) :pMin(p), pMax(p) {}
			BBox(const BBox& p) :pMin(p.pMin), pMax(p.pMax) {}
			BBox(const Point& p1, const Point& p2)
			{
				pMin = Point(std::min(p1[0], p2[0]), std::min(p1[1], p2[1]), std::min(p1[2], p2[2]));
				pMax = Point(std::max(p1[0], p2[0]), std::max(p1[1], p2[1]), std::max(p1[2], p2[2]));
			}

			BBox& operator+=(const BBox& b) {
				pMin = Point(std::min(b.pMin[0], pMin[0]), std::min(b.pMin[1], pMin[1]), std::min(b.pMin[2], pMin[2]));
				pMax = Point(std::max(b.pMax[0], pMax[0]), std::max(b.pMax[1], pMax[1]), std::max(b.pMax[2], pMax[2]));
				return *this;
			}

			BBox& operator+=(const Point& p){
				pMin = Point(std::min(p[0], pMin[0]), std::min(p[1], pMin[1]), std::min(p[2], pMin[2]));
				pMax = Point(std::max(p[0], pMax[0]), std::max(p[1], pMax[1]), std::max(p[2], pMax[2]));
				return *this;
			}

			BBox& operator+=(float delta) {
				Vector v(delta, delta, delta);
				pMin -= v ;
				pMax += v;
				return *this;
			}

			BBox operator+(const BBox& b) const
			{
				BBox ret(*this);
				ret += b;
				return ret;
			}

			BBox operator+(const Point& p) const
			{
				BBox ret(*this);
				ret += p;
				return ret;
			}

			BBox operator+(float delta) const
			{
				BBox ret(*this);
				ret += delta;
				return ret;
			}

			bool isIncluding(const Point& p) {
				return (p[0] >= pMin[0] && p[0] <= pMax[0] &&
					p[1] >= pMin[1] && p[1] <= pMax[1] &&
					p[2] >= pMin[2] && p[2] <= pMax[2]);
			}

			bool isIncluding(const BBox& b) {
				return isIncluding(b.pMin) && isIncluding(b.pMax);
			}

			bool isIntersecting(const BBox& b) {
				return !((b.pMin[0] > pMax[0] && b.pMin[0] > pMax[0] && b.pMin[0] > pMax[0]) &&
					(b.pMax[0] < pMin[0] && b.pMax[0] < pMin[0] && b.pMax[0] < pMin[0]));
			}

			axis maxAxis()
			{
				Vector diagonal = pMax - pMin;
				if (diagonal[0] > diagonal[1] && diagonal[0] > diagonal[2])
					return X;
				else if (diagonal[1] > diagonal[2])
					return Y;
				else
					return Z;
			}

			bool intersectP(const Ray& ray, float* hit0 = NULL, float* hit1 = NULL)
			{

				return true;
			}
		};
	}//namespace BASE
}//namespace PBRT