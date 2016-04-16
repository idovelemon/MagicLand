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

namespace MagicLand 
{ 
	class MLComDir;
	class MLComponent;
};

class MagicLand::MLComDir:public MLComponent
{
public:
	MLComDir(MagicLand::MLEntity* entity, MagicLand::MLDir dir);
	virtual ~MLComDir();

public:
	void SetDir(MagicLand::MLDir dir);
	MagicLand::MLDir GetDir();

protected:
	MagicLand::MLDir m_Dir;
};

#endif // ML_ENTITYCOMPONENT_MLCOMDIR_H_