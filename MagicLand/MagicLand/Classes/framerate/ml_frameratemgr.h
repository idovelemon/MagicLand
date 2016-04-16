//---------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 07
// Version: 1.0
// Brief: This file will define the frame rate manager
//---------------------------------------------------------------------------
#ifndef ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_
#define ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_

namespace MagicLand { class MLFrameRateMgr; };

class MagicLand::MLFrameRateMgr
{
protected:
	MLFrameRateMgr();
	virtual ~MLFrameRateMgr();

public:
	static MLFrameRateMgr* SharedInstance();

public:
	void AddDelta(float delta);
	float GetFrameDelta() const;
	long GetTotalFrames() const;
	float GetTotalTime() const;

protected:
	static MLFrameRateMgr* s_Instance;
	float m_FrameDelta;
	long m_TotalFrames;
	float m_TotalTime;
};

#endif // ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_