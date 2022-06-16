#include "myVector3.h"
#include <cmath>

myVector3::myVector3() :x(0), y(0), z(0)
{}

myVector3::myVector3(float x, float y, float z) : x(x), y(y), z(z)
{

}

float myVector3::length() const
{
	return std::sqrt(x * x + y * y);
}

myVector3& myVector3::normalize()
{
	float len = length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float myVector3::dot(const myVector3& v) const
{
	return x * v.x + y * v.y;
}

myVector3 myVector3::cross(const myVector3& v) const
{
	return myVector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

myVector3 myVector3::cross2(const myVector3& v, const myVector3& s) const
{
	return myVector3(
		v.y * s.z - v.z * s.y,
		v.z * s.x - v.x * s.z,
		v.x * s.y - v.y * s.x
	);
}

myVector3 myVector3::faceNormal(const myVector3& v0, const myVector3& v1, const myVector3& v2)
{
	myVector3 n;

	// 頂点を結ぶベクトルを算出
	myVector3 vec1 = { v1.x - v0.x, v1.y - v0.y, v1.z - v0.z };
	myVector3 vec2 = { v2.x - v0.x, v2.y - v0.y, v2.z - v0.z };

	// ベクトル同士の外積
	n.x = vec1.y * vec2.z - vec1.z * vec2.y;
	n.y = vec1.z * vec2.x - vec1.x * vec2.z;
	n.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return n;
}

myVector3 myVector3::vertexNormal(const myVector3& v1, const myVector3& v2, const myVector3& v3)
{
	myVector3 n;

	n.x = (v1.x + v2.x + v3.x) / 3;
	n.y = (v1.y + v2.y + v3.y) / 3;
	n.z = (v1.z + v2.z + v3.z) / 3;

	return n;
}



myVector3 myVector3::operator+()const
{
	return *this;
}

myVector3 myVector3::operator-()const
{
	return myVector3(-*this);
}

myVector3& myVector3::operator+=(const myVector3& v)
{
	this->x += v.x;
	this->y += v.y;

	return *this;
}

myVector3& myVector3::operator-=(const myVector3& v)
{
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}

myVector3& myVector3::operator*=(float s)
{
	this->x = s;
	this->y = s;

	return *this;
}


myVector3& myVector3::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

//Vector3 クラスに属さない関数群
//2項演算子
const myVector3 operator + (const myVector3& v1, const myVector3& v2)
{
	myVector3 temp(v1);
	return temp += v2;
}

const myVector3 operator - (const myVector3& v1, const myVector3& v2)
{
	myVector3 temp(v1);
	return temp -= v2;
}

const myVector3 operator *(const myVector3& v, float s)
{
	myVector3 temp(v);
	return temp * s;
}

const myVector3 operator *(float s, const myVector3& v)
{
	return v * s;
}

const myVector3 operator/(const myVector3& v, float s)
{
	myVector3 temp(v);
	return temp / s;
}