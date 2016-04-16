//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/20
// Version: 1.0
// Breif: This file will define the bounding box of the entity.The game
// will do collision test on this component.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMBOUNDBOX_H_
#define ML_ENTITYCOMPONENT_MLCOMBOUNDBOX_H_

#include<vector>

#include "entitycomponent/ml_component.h"
#include "support/xjmath/XJMath.h"

namespace MagicLand 
{ 
	class MLComBoundBox;
	typedef std::vector<MLEntity*> MLColVector;
	class MLComponent;
	class MLEntity;
};

class MagicLand::MLComBoundBox:public MLComponent
{
public:
	MLComBoundBox(MagicLand::MLEntity* entity, float width, float height, float posx, float posy);
	virtual ~MLComBoundBox();

public:
	virtual void	SetBoundBox(AABB aabb);
	virtual AABB	GetBoundBox() const;
	virtual void	AddEntity(MagicLand::MLEntity* colEntity);
	virtual bool	IsCollided() const;
	virtual MagicLand::MLColVector&	GetColEntities();
	virtual void	UpdateBoundBox(VECTOR2 pos);
	virtual void	Reset();

protected:
	AABB					m_Aabb;			// The bounding box of the entity
	bool					m_IsCollided;	// If the bound box has collided with other bound box
	MagicLand::MLColVector	m_ColEntities;	// The collided entities
};

#endif // ML_ENTITYCOMPONENT_MLCOMBOUNDBOX_H_