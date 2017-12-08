#pragma once
#include "Vector3f.h"
#include "Color4f.h"
#include "Quaternion.h"

class Entity
{
public:
	float	m;        // Значение массы.
	float	r;
	Vector3f  pos;      // Положение в пространстве.
	Quaternion	q;		// Положение в пространстве.
	Vector3f  vel;      // Скорость.
	Vector3f  force;    // Воздействующая сила.
	Color4f   color;


	Entity():m(1.0f), r(1.0f)
	{
	}

	virtual ~Entity()
	{
	}

	virtual void applyForce(Vector3f _force);

	virtual void init();	// Обнуляем «нашу» силу

	virtual void simulate(float dt);

	virtual void draw() {};

};

inline void Entity::applyForce(Vector3f _force)
{
	force += _force;    // Внешнюю силу прибавляем к «нашей».
}

inline void Entity::init()          // Обнуляем «нашу» силу
{
	force.x = 0;
	force.y = 0;
	force.z = 0;
}

inline void Entity::simulate(float dt)
{
	vel += (force / m) * dt;  // Изменение в скорости добавляем к текущей скорости. Изменение пропорционально ускорению (сила/масса) и изменению времени
	pos += vel * dt;          // Изменение в положении добавляем к текущему положению. Изменение в положении Скорость*время
}

