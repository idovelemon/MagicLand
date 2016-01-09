//----------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the timer component in this game
//---------------------------------------------------------------------
#ifndef __MLCOMTIMER__H_
#define __MLCOMTIMER__H_

#include "MLComponent.h"
#include <map>

namespace MagicLand { class MLComTimer; };

class MagicLand::MLComTimer:public MagicLand::MLComponent
{
public:
	MLComTimer(MagicLand::MLEntity* entity);
	virtual ~MLComTimer();

public:
	void AddTimer(unsigned int flag, float initTime = 0.0f);
	float GetTimer(unsigned int flag);
	void UpdateTimer(unsigned int flag, float curTime);

protected:
	typedef std::map<unsigned int, float> MLTimerMap;
	MLTimerMap m_TimerMap;
};

#endif