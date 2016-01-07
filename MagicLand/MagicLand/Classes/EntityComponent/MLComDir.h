//---------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the direction component
//---------------------------------------------------------
#ifndef __MLCOMDIR__H_
#define __MLCOMDIR__H_

#include "MLComponent.h"
#include "MLEntity.h"

namespace MagicLand { class MLComDir; };

class MagicLand::MLComDir:public MLComponent
{
public:
	MLComDir(MagicLand::MLEntity* pEntity, MagicLand::MLDir dir);
	virtual ~MLComDir();

public:
	void SetDir(MagicLand::MLDir dir);
	MagicLand::MLDir GetDir();

protected:
	MagicLand::MLDir m_Dir;
};

#endif