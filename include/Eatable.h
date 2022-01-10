#pragma once

#include "ObjectBase.h"

class Eatable : public ObjectBase
{
public:
	using ObjectBase::ObjectBase;
	virtual void handleCollision(DynamicObject& gameObject);
private:
};