#pragma once
#include "../Math/Vector3.h"

class BaseEntity
{
public:
	BaseEntity() {}
	virtual ~BaseEntity() {}
	BaseEntity(const Vector3& pos_);
	BaseEntity(const BaseEntity& be_);
protected:
	Vector3 pos;
};

inline BaseEntity::BaseEntity(const Vector3& pos_)
:pos(pos_)
{
}

inline BaseEntity::BaseEntity(const BaseEntity& be_)
{
	*this = be_;
}