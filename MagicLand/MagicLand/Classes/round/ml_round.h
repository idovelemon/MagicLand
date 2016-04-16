//-----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 07
// Version: 1.0
// Brief: This file will define the round in this game
//-----------------------------------------------------------------------------
#ifndef ML_ROUND_MLROUND_H_
#define ML_ROUND_MLROUND_H_

#include "reference/ml_reference.h"

namespace MagicLand 
{ 
	class MLRound;
	class MLRoom;
};

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

#endif // ML_ROUND_MLROUND_H_