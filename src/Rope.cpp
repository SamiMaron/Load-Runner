#include "Rope.h"
#include "Ladder.h"
#include "DynamicObject.h"

//send to dynamic object tell him that he on rope
void Rope::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
