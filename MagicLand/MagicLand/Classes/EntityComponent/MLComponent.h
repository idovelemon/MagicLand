//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define the component interface that will be used in
// MagicLand with the Entity-Component architecture
//------------------------------------------------------------------------
#ifndef __MLCOMPONENT__H_
#define __MLCOMPONENT__H_

#include "../Reference/MLReference.h"

namespace MagicLand
{ 
	class MLComponent;
	class MLEntity;

	enum MLComType
	{
		ML_COMTYPE_NONE = -1,
		ML_COMTYPE_DISPLAY,		// This enum indicate the display component
		ML_COMTYPE_TRANSFORM,	// This enum indicate the position,rotation and scale of the entity
		ML_COMTYPE_BOUNDBOX,	// This enum indicate the bounding box of the entity
		ML_COMTYPE_STATE,		// This enum indicate the state of the entity
		ML_COMTYPE_MOVEMENT,	// This enum indicate the movement of the entity
		ML_COMTYPE_DIR,			// This enum indicate the direction of the entity
		ML_COMTYPE_TIMER,		// This enum indicate the timer component

		// User define component
		ML_COMTYPE_ORGE_WALKRANGE,

		ML_COMTYPE_TOTAL,		// This enum indicate how many component's type in MagicLand
	};
};

class MagicLand::MLComponent:public MLReference
{
public:
	MLComponent(MLComType type, MagicLand::MLEntity* entity);
    virtual ~MLComponent();

public:
    virtual MLComType GetType() const;

protected:
    MLComType m_Type;
	MagicLand::MLEntity* m_Entity;
};

#endif