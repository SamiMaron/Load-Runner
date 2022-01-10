#pragma once

#include "wall.h"


class Rope : public ObjectBase
{
	using ObjectBase::ObjectBase;
	virtual void handleCollision(DynamicObject& gameObject);
};