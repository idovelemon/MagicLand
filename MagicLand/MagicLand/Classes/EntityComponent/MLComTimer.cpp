#include "MLComTimer.h"
#include "../marco.h"
using namespace MagicLand;

MLComTimer::MLComTimer(MLEntity* entity)
	:MLComponent(ML_COMTYPE_TIMER, entity)
{
	m_TimerMap.clear();
}

MLComTimer::~MLComTimer()
{
}

void MLComTimer::AddTimer(unsigned int flag, float initTime)
{
	MLTimerMap::iterator it = m_TimerMap.find(flag);
	ML_SAFE_ASSERT(it == m_TimerMap.end(), "Please make sure the flag of the timer is unique");
	m_TimerMap.insert(std::pair<unsigned int, float>(flag, initTime));
}

float MLComTimer::GetTimer(unsigned int flag)
{
	MLTimerMap::iterator it = m_TimerMap.find(flag);
	ML_SAFE_ASSERT(it != m_TimerMap.end(), "Please make sure the timer exsits");
	return it->second;
}

void MLComTimer::UpdateTimer(unsigned int flag, float time)
{
	MLTimerMap::iterator it = m_TimerMap.find(flag);
	ML_SAFE_ASSERT(it != m_TimerMap.end(), "Please make sure the timer exsits");
	it->second = time;
}