#pragma once
#include "Geometry.h"
#include <iostream>
using namespace std;

void Vector_UnitTest()
{
	using namespace PBRT::BASE;
	cout << "Vector_UnitTest Begin:" << endl;
	Vector v(1, 2, 3);
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	v *= 5;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	Vector v1(1, 2, 3);
	v += v1;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;

	v = 3 * v;
	cout << v[0] << " " << v[1] << " " << v[2] << endl;

	cout << Dot(v, v1) << endl;
	cout << "Vector_UnitTest End:" << endl;
}

void Point_UnitTest()
{
	using namespace PBRT::BASE;
	cout << "Point_UnitTest Begin:" << endl;
	Point v(1, 2, 3);
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	v *= 5;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	Vector v1(1, 2, 3);
	v += v1;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	v -= v1;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	cout << v[0] << " " << v[1] << " " << v[2] << endl;
	cout << "Point_UnitTest End:" << endl;
}

void Normal_UnitTest()
{
	using namespace PBRT::BASE;
	cout << "Normal_UnitTest Begin:" << endl;
	Normal v(1, 2, 3);
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	v *= 5;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	Normal v1(1, 2, 3);
	v += v1;
	cout << v.value.ff.x << " " << v.value.ff.y << " " << v.value.ff.z << endl;
	cout << v[0] << " " << v[1] << " " << v[2] << endl;
	cout << "Normal_UnitTest End:" << endl;
}

void Ray_UnitTest()
{
	using namespace PBRT::BASE;
	cout << "Ray_UnitTest Begin:" << endl;
	Point o(3, 4, 5);
	Vector d(2, 4, 8);
	Ray v(o, d, 3);
	Point p = v(5);
	cout << p[0] << " " << p[1] << " " << p[2] << endl;
	cout << "Ray_UnitTest End:" << endl;
}
