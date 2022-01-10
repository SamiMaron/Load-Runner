#include "EnemyPresent.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with taking a enemy present
void EnemyPresent::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
