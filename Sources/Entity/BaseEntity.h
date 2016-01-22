#pragma once
#include "../Math/Vector3f.h"

class BaseEntity
{
public:
	BaseEntity();
	virtual ~BaseEntity();
	BaseEntity(const Vector3f& pos_);
	BaseEntity(const BaseEntity& be_);

	Vector3f GetPos()
	{
		return pos;
	}

	void SetPos(const Vector3f& pos_)
	{
		pos = pos_;
	}

private:
	Vector3f pos;
};

inline BaseEntity::BaseEntity()
:pos(0.0, 0.0, 0.0)
{
}

inline BaseEntity::~BaseEntity()
{
}

inline BaseEntity::BaseEntity(const Vector3f& pos_)
:pos(pos_)
{
}

inline BaseEntity::BaseEntity(const BaseEntity& be_)
{
	*this = be_;
}