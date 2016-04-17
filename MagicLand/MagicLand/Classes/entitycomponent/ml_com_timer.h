//----------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the timer component in this game
//---------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMTIMER_H_
#define ML_ENTITYCOMPONENT_MLCOMTIMER_H_

#include <map>

#include "marco.h"
#include "entitycomponent/ml_component.h"

namespace magicland {

class MLComTimer:public MLComponent {
public:
	MLComTimer(magicland::MLEntity* entity);
	virtual ~MLComTimer();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComTimer);

public:
	void AddTimer(unsigned int flag, float initTime = 0.0f);
	float GetTimer(unsigned int flag);
	void UpdateTimer(unsigned int flag, float curTime);

protected:
	typedef std::map<unsigned int, float> MLTimerMap;
	MLTimerMap m_TimerMap;
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLCOMTIMER_H_