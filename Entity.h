#pragma once
#include "Vector3f.h"
#include "Color4f.h"
#include "Quaternion.h"

class Entity
{
public:
	float	m;        // �������� �����.
	float	r;
	Vector3f  pos;      // ��������� � ������������.
	Quaternion	q;		// ��������� � ������������.
	Vector3f  vel;      // ��������.
	Vector3f  force;    // �������������� ����.
	Color4f   color;


	Entity():m(1.0f), r(1.0f)
	{
	}

	virtual ~Entity()
	{
	}

	virtual void applyForce(Vector3f _force);

	virtual void init();	// �������� ����� ����

	virtual void simulate(float dt);

	virtual void draw() {};

};

inline void Entity::applyForce(Vector3f _force)
{
	force += _force;    // ������� ���� ���������� � ������.
}

inline void Entity::init()          // �������� ����� ����
{
	force.x = 0;
	force.y = 0;
	force.z = 0;
}

inline void Entity::simulate(float dt)
{
	vel += (force / m) * dt;  // ��������� � �������� ��������� � ������� ��������. ��������� ��������������� ��������� (����/�����) � ��������� �������
	pos += vel * dt;          // ��������� � ��������� ��������� � �������� ���������. ��������� � ��������� ��������*�����
}

