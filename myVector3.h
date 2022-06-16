#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
class myVector3 {
public:
	float x; // x成分
	float y; // y成分
	float z; // z成分

public:

	// コンストラクタ
	myVector3();                          // 零ベクトルとする
	myVector3(float x, float y, float z); // x成分, y成分, z成分 を指定しての生成

	//メンバ関数
	float length() const; //ノルム(長さ)を求める
	myVector3& normalize(); //正規化する
	float dot(const myVector3& v) const; //内積を求める
	myVector3 cross(const myVector3& v) const; //外積を求める
	myVector3 cross2(const myVector3& v, const myVector3& s) const;
	myVector3 faceNormal(const myVector3& v1, const myVector3& v2, const myVector3& v3);

	myVector3 vertexNormal(const myVector3& v1, const myVector3& v2, const myVector3& v3);

	// 単項演算子オーバーロード
	myVector3 operator+() const;
	myVector3 operator-() const;

	// 代入演算子オーバーロード
	myVector3& operator+=(const myVector3& v);
	myVector3& operator-=(const myVector3& v);
	myVector3& operator*=(float s);
	myVector3& operator/=(float s);
};

//2項演算子オーバーロード
// ※いろんな引数のパターンに対応(引数の順序)するため,以下のように準備している
const myVector3 operator+(const myVector3& v1, const myVector3& v2);
const myVector3 operator-(const myVector3& v1, const myVector3& v2);
const myVector3 operator*(const myVector3& v, float s);
const myVector3 operator*(float s, const myVector3& v);
const myVector3 operator/(const myVector3& v, float s);