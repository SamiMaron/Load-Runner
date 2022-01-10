#pragma once

#include "Eatable.h"


class PointsPresent : public Eatable
{
	using Eatable::Eatable;
	virtual void handleCollision(DynamicObject& gameObject);
};