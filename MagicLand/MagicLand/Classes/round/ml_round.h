//-----------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 07
// Version: 1.0
// Brief: This file will define the round in this game
//-----------------------------------------------------------------------------
#ifndef ML_ROUND_MLROUND_H_
#define ML_ROUND_MLROUND_H_

#include "marco.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLRoom;

class MLRound:public MLReference
{
public:
	static MLRound* SharedInstance();
	static void Destroy();

	virtual void Update(float delta);
	virtual magicland::MLRoom* GetCurRoom() const;

protected:
  MLRound();
	virtual ~MLRound();

	magicland::MLRoom* m_CurRoom;
	static MLRound* s_Instance;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLRound);
};

};

#endif // ML_ROUND_MLROUND_H_