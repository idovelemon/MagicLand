//------------------------------------------------------------------------
// Declaration: Copyright (c), by LiaoYuhang, 2015. All right reserved.
// Author: LiaoYuhang
// Date: 2016/01/02
// Version: 1.0
// Brief: 
//------------------------------------------------------------------------
#ifndef __MLPLAYERCAMERA__H_
#define __MLPLAYERCAMERA__H_

#include "../MLCamera.h"

namespace MagicLand
{
	class MLPlayerCamera;
};

class MagicLand::MLPlayerCamera : public MLCamera
{
public:
	MLPlayerCamera();
	MLPlayerCamera(CCLayer* layer);
	virtual ~MLPlayerCamera();

public:
	virtual bool Init();
	virtual void Update(float delta);
	virtual void Kill();

private:
	void calculateCamrea();

public:
	virtual bool IsDead() const;
};

#endif