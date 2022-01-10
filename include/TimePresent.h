#pragma once

#include "Eatable.h"


class TimePresent : public Eatable
{
	using Eatable::Eatable;
	virtual void handleCollision(DynamicObject& gameObject);
};