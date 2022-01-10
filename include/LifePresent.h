#pragma once

#include "Eatable.h"


class LifePresent : public Eatable
{
	using Eatable::Eatable;
	virtual void handleCollision(DynamicObject& gameObject);
};