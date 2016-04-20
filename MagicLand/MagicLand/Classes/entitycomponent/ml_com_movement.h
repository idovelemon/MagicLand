//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the movment component which hold all the movement parameters.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_
#define ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_

#include "entitycomponent/ml_component.h"

#include "marco.h"
#include "support/xjmath/XJMath.h"

namespace magicland {

class MLComMovement:public MLComponent {
public:
	MLComMovement(magicland::MLEntity* entity);
	virtual ~MLComMovement();

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

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComMovement);
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLCOMMOVEMENT_H_