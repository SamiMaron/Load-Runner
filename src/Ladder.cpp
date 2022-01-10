#include "Ladder.h"
#include "DynamicObject.h"

//send to dynamic object tell him that he on ladder
void Ladder::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
