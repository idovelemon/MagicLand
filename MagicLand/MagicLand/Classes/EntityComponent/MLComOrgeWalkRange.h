//--------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the orge's walk range component
//--------------------------------------------------------------------------
#ifndef __MLCOMORGEWALKRANGE__H_
#define __MLCOMORGEWALKRANGE__H_

#include "MLComponent.h"

namespace MagicLand { class MLComOrgeWalkRange; };

class MagicLand::MLComOrgeWalkRange:public MagicLand::MLComponent
{
public:
	//-----------------------------------------------------------------------
	// Desc: This method will constructor the MLComOrgeWalkRange component.
	// This component define the walk range of the orge which means the orge
	// will only walk in this range.The range is defined by center point and the width.
	// For example:
	// Center Point: 10
	// Width: 30
	// Then the range is [-5, 25]
	// Another thing to remember is that the range only work at x-axis.
	//-----------------------------------------------------------------------
	MLComOrgeWalkRange(MagicLand::MLEntity* entity, float centerX, float width);
	virtual ~MLComOrgeWalkRange();

public:
	float GetCenterX();
	float GetWidth();

protected:
	float m_CenterPosX;
	float m_Width;
};

#endif