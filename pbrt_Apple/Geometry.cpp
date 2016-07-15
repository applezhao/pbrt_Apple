#include "Geometry.h"

namespace PBRT {
	namespace BASE {
		Vector operator*(float f, const Vector& v) {
			__m128 m_f = _mm_set_ps1(f);
			return Vector(_mm_mul_ps(v.value.mm, m_f));
		}

		Vector operator*(const Vector& v, float f) {
			__m128 m_f = _mm_set_ps1(f);
			return Vector(_mm_mul_ps(v.value.mm, m_f));
		}

		float Dot(const Vector& v1, const Vector& v2) {
			return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
		}

		float Dot(const Vector& v1, const Normal& v2) {
			return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
		}

		float Dot(const Normal& v1, const Vector& v2) {
			return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
		}

		Vector Cross(const Vector& v1, const Vector& v2) {
			return Vector(v1[1] * v2[2] - v1[2] * v2[1],
				v1[2] * v2[0] - v1[0] * v2[2],
				v1[0] * v2[1] - v1[1] * v2[0]);
		}

		Vector Cross(const Vector& v1, const Normal& v2) {
			return Vector(v1[1] * v2[2] - v1[2] * v2[1],
				v1[2] * v2[0] - v1[0] * v2[2],
				v1[0] * v2[1] - v1[1] * v2[0]);
		}

		Vector Cross(const Normal& v1, const Vector& v2) {
			return Vector(v1[1] * v2[2] - v1[2] * v2[1],
				v1[2] * v2[0] - v1[0] * v2[2],
				v1[0] * v2[1] - v1[1] * v2[0]);
		}

		Vector Normalize(const Vector& v) {
			return v / v.Length();
		}
	}
}