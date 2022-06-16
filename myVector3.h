#pragma once

/// <summary>
/// 3�����x�N�g��
/// </summary>
class myVector3 {
public:
	float x; // x����
	float y; // y����
	float z; // z����

public:

	// �R���X�g���N�^
	myVector3();                          // ��x�N�g���Ƃ���
	myVector3(float x, float y, float z); // x����, y����, z���� ���w�肵�Ă̐���

	//�����o�֐�
	float length() const; //�m����(����)�����߂�
	myVector3& normalize(); //���K������
	float dot(const myVector3& v) const; //���ς����߂�
	myVector3 cross(const myVector3& v) const; //�O�ς����߂�
	myVector3 cross2(const myVector3& v, const myVector3& s) const;
	myVector3 faceNormal(const myVector3& v1, const myVector3& v2, const myVector3& v3);

	myVector3 vertexNormal(const myVector3& v1, const myVector3& v2, const myVector3& v3);

	// �P�����Z�q�I�[�o�[���[�h
	myVector3 operator+() const;
	myVector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	myVector3& operator+=(const myVector3& v);
	myVector3& operator-=(const myVector3& v);
	myVector3& operator*=(float s);
	myVector3& operator/=(float s);
};

//2�����Z�q�I�[�o�[���[�h
// �������Ȉ����̃p�^�[���ɑΉ�(�����̏���)���邽��,�ȉ��̂悤�ɏ������Ă���
const myVector3 operator+(const myVector3& v1, const myVector3& v2);
const myVector3 operator-(const myVector3& v1, const myVector3& v2);
const myVector3 operator*(const myVector3& v, float s);
const myVector3 operator*(float s, const myVector3& v);
const myVector3 operator/(const myVector3& v, float s);