#pragma once

#include "ObjectBase.h"

class Ladder : public ObjectBase
{
	using ObjectBase::ObjectBase;
	virtual void handleCollision(DynamicObject& gameObject);
};