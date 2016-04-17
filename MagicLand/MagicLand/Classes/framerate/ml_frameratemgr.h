//---------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 07
// Version: 1.0
// Brief: This file will define the frame rate manager
//---------------------------------------------------------------------------
#ifndef ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_
#define ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_

#include "marco.h"

namespace magicland {
	
class MLFrameRateMgr {
protected:
	MLFrameRateMgr();
	virtual ~MLFrameRateMgr();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLFrameRateMgr);

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

}; // namespace magicland

#endif // ML_ENTITYCOMONENT_MLFRAMERATEMGR_H_