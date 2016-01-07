//-----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 07
// Version: 1.0
// Brief: This file will define the round in this game
//-----------------------------------------------------------------------------
#ifndef __MLROUND__H_
#define __MLROUND__H_

#include "MLRoom.h"
#include "../Reference/MLReference.h"

namespace MagicLand { class MLRound; };

class MagicLand::MLRound:public MLReference
{
protected:
	MLRound();
	virtual ~MLRound();

public:
	static MLRound* SharedInstance();
	static void Destroy();

public:
	virtual void Update(float delta);
	virtual MagicLand::MLRoom* GetCurRoom() const;

protected:
	MagicLand::MLRoom* m_CurRoom;
	static MLRound* s_Instance;
};

#endif