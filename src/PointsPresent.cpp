#include "PointsPresent.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with taking a point present
void PointsPresent::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
