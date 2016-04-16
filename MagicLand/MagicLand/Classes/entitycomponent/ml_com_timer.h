//----------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the timer component in this game
//---------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMTIMER_H_
#define ML_ENTITYCOMPONENT_MLCOMTIMER_H_

#include <map>

#include "entitycomponent/ml_component.h"

namespace magicland { class MLComTimer; };

class magicland::MLComTimer:public magicland::MLComponent
{
public:
	MLComTimer(magicland::MLEntity* entity);
	virtual ~MLComTimer();

public:
	void AddTimer(unsigned int flag, float initTime = 0.0f);
	float GetTimer(unsigned int flag);
	void UpdateTimer(unsigned int flag, float curTime);

protected:
	typedef std::map<unsigned int, float> MLTimerMap;
	MLTimerMap m_TimerMap;
};

#endif // ML_ENTITYCOMPONENT_MLCOMTIMER_H_