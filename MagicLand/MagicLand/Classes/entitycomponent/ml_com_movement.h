//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the movment component which hold all the movement parameters.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_
#define ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_

#include "ml_component.h"

#include "../support/xjmath/XJMath.h"

namespace MagicLand 
{ 
	class MLComMovement;
};

class MagicLand::MLComMovement:public MLComponent
{
public:
	MLComMovement(MagicLand::MLEntity* entity);
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

#endif // ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_