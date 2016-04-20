//---------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the direction component
//---------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMDIR_H_
#define ML_ENTITYCOMPONENT_MLCOMDIR_H_

#include "marco.h"
#include "entitycomponent/ml_entity.h" // TODO(i_dovelemon):Split the game's entity type with the Framework

namespace magicland {

class MLComponent;

class MLComDir:public MLComponent {
public:
	MLComDir(magicland::MLEntity* entity, magicland::MLDir dir);
	virtual ~MLComDir();

	void SetDir(magicland::MLDir dir);
	magicland::MLDir GetDir();

protected:
	magicland::MLDir m_Dir;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComDir);
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLCOMDIR_H_