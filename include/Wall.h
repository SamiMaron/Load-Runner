#pragma once

#include "ObjectBase.h"

class Wall : public ObjectBase
{
	using ObjectBase::ObjectBase;

	virtual void setDig();
	virtual bool isDig()const;
	virtual void setDigTime();
	virtual void handleCollision(DynamicObject& gameObject);
	void setOverDig();
	virtual bool digOver();
	virtual bool dynamicOndig();
	virtual void setDynamicOnDig();
private:
	bool m_releasefromdig = false;
	bool m_thereisdynamic = false;
	bool m_dig = false;
	float m_time;
	Clock m_clock;
};