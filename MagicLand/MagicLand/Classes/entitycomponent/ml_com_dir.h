//---------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the direction component
//---------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMDIR_H_
#define ML_ENTITYCOMPONENT_MLCOMDIR_H_

#include "entitycomponent/ml_entity.h" // FixMe:Split the game's entity type with the Framework

namespace magicland 
{ 
	class MLComDir;
	class MLComponent;
};

class magicland::MLComDir:public MLComponent
{
public:
	MLComDir(magicland::MLEntity* entity, magicland::MLDir dir);
	virtual ~MLComDir();

public:
	void SetDir(magicland::MLDir dir);
	magicland::MLDir GetDir();

protected:
	magicland::MLDir m_Dir;
};

#endif // ML_ENTITYCOMPONENT_MLCOMDIR_H_