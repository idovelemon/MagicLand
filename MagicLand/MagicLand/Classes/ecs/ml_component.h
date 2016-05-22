//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define the component interface that will be used in
// magicland with the Entity-Component architecture
//------------------------------------------------------------------------
#ifndef ML_ECS_MLCOMPONENT_H_
#define ML_ECS_MLCOMPONENT_H_

#include "marco.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

enum MLComType
{
	ML_COMTYPE_NONE = -1,
	ML_COMTYPE_DISPLAY,		// This enum indicate the display component
	ML_COMTYPE_TRANSFORM,	// This enum indicate the position,rotation and scale of the entity
	ML_COMTYPE_TIMER,		  // This enum indicate the timer component
	ML_COMTYPE_USERDATA,	// This enum indicate the user data component
  ML_COMTYPE_WEAPONS,
  ML_COMTYPE_SPEED,

	// User define component

	ML_COMTYPE_TOTAL,		// This enum indicate how many component's type in magicland
};

class MLComponent:public MLReference {
public:
	MLComponent(MLComType type, magicland::MLEntity* entity);
  virtual ~MLComponent();

  virtual MLComType GetType() const;

  virtual void Run(float delta);

protected:
  MLComType m_Type;
	magicland::MLEntity* m_Entity;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComponent);
};

}; // namespace magicland

#endif // ML_ECS_MLCOMPONENT_H_