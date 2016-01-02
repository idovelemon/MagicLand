//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the movment component which hold all the movement parameters.
//------------------------------------------------------------------------
#ifndef __MLCOMMOVEMENT__H_
#define __MLCOMMOVEMENT__H_

#include "MLComponent.h"
#include "../Support/XJMath/XJMath.h"

namespace MagicLand { class MLComMovement; };

class MagicLand::MLComMovement:public MLComponent
{
public:
	MLComMovement(MagicLand::MLEntity* pEntity);
	virtual ~MLComMovement();

public:
	virtual void SetVel(float x, float y);
	virtual VECTOR2 GetVel() const;
	virtual void SetGravity(float g);
	virtual float GetGravity() const;
	virtual void SetMaxFallSpeed(float max);
	virtual float GetMaxFallSpeed() const;

protected:
	VECTOR2	m_Vel;	
	float	m_Gravity;
	float	m_MaxFallSpeed;
};

#endif