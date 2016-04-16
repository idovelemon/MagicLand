//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/20
// Version: 1.0
// Breif: This file will define the transform of the entity.The transform
// hold all the position, rotation and the scale of the entity.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMONENT_MLCOMTRANSFORM_H_
#define ML_ENTITYCOMONENT_MLCOMTRANSFORM_H_

#include "entitycomponent/ml_component.h"
#include "support/xjmath/XJMath.h"

namespace MagicLand { class MLComTransform;};

class MagicLand::MLComTransform:public MagicLand::MLComponent
{
public:
	MLComTransform(MagicLand::MLEntity* entity, float x, float y, float sx, float sy, float r);
	virtual ~MLComTransform();

public:
	virtual void	SetPos(float x, float y);
	virtual VECTOR2	GetPos() const;

	virtual void	SetScale(float sx, float sy);
	virtual VECTOR2 GetScale() const;

	virtual void	SetRot(float r);
	virtual float	GetRot() const;

protected:
	VECTOR2 m_Pos;		// The position of the entity
	VECTOR2 m_Scale;	// The scale of the entity
	float	m_Rot;		// The rotation of the entity in degree
};
#endif // ML_ENTITYCOMONENT_MLCOMTRANSFORM_H_