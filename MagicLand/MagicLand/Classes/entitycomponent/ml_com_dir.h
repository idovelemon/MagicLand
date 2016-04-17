//---------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the direction component
//---------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMDIR_H_
#define ML_ENTITYCOMPONENT_MLCOMDIR_H_

#include "marco.h"
#include "entitycomponent/ml_entity.h" // FixMe:Split the game's entity type with the Framework

namespace magicland {

class MLComponent;

class MLComDir:public MLComponent {
public:
	MLComDir(magicland::MLEntity* entity, magicland::MLDir dir);
	virtual ~MLComDir();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComDir);

public:
	void SetDir(magicland::MLDir dir);
	magicland::MLDir GetDir();

protected:
	magicland::MLDir m_Dir;
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLCOMDIR_H_