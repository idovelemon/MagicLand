#include "framerate/ml_frameratemgr.h"

using namespace magicland;

MLFrameRateMgr* MLFrameRateMgr::s_Instance = 0;

MLFrameRateMgr::MLFrameRateMgr()
	:m_FrameDelta(0.0f)
	,m_TotalFrames(0)
	,m_TotalTime(0.0f)
{
}

MLFrameRateMgr::~MLFrameRateMgr()
{
}

MLFrameRateMgr* MLFrameRateMgr::SharedInstance()
{
	if(s_Instance == 0)
	{
		static MLFrameRateMgr frameRateMgr;
		s_Instance = &frameRateMgr;
	}

	return s_Instance;
}

void MLFrameRateMgr::AddDelta(float delta)
{
	m_FrameDelta = delta;
	m_TotalFrames++;
	m_TotalTime += delta;
}

float MLFrameRateMgr::GetFrameDelta() const
{
	return m_FrameDelta;
}

long MLFrameRateMgr::GetTotalFrames() const
{
	return m_TotalFrames;
}

float MLFrameRateMgr::GetTotalTime() const
{
	return m_TotalTime;
}