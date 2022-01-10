#pragma once

#include "Eatable.h"

class EnemyPresent : public Eatable
{
	using Eatable::Eatable;
	virtual void handleCollision(DynamicObject& gameObject);
};