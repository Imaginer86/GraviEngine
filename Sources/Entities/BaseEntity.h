#pragma once
#include "../Math/Vector3d.h"

class BaseEntity
{
public:
	BaseEntity() {}
	virtual ~BaseEntity() {}
	BaseEntity(const Vector3d& pos_);
	BaseEntity(const BaseEntity& be_);

	Vector3d GetPos()
	{
		return pos;
	}

	void SetPos(const Vector3d& pos_)
	{
		this->pos = pos_;
	}

private:
	Vector3d pos;
};

inline BaseEntity::BaseEntity(const Vector3d& pos_)
:pos(pos_)
{
}

inline BaseEntity::BaseEntity(const BaseEntity& be_)
{
	*this = be_;
}