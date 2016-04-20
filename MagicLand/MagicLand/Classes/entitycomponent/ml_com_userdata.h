//---------------------------------------------------------
// Declaration: Copyright (c) 2016. All right reserved.
// Author:
// Date: 2016 / 01 / 12
// Version: 1.0
// Brief:
//---------------------------------------------------------
#ifndef ML_ENTITYCOMONENT_MLCOMUSERDATA_H_
#define ML_ENTITYCOMONENT_MLCOMUSERDATA_H_

#include <vector>

#include "marco.h"
#include "entitycomponent/ml_component.h"

namespace magicland {

class MLComUserData:public MLComponent
{
public:
  enum USER_DATA_TYPE
	{
		USER_DATA_TYPE_INTEGER,
		USER_DATA_TYPE_FLOAT,
		USER_DATA_TYPE_POINTER,

		USER_DATA_TYPE_MAX
	};

	explicit MLComUserData(magicland::MLEntity* entity);
	virtual ~MLComUserData();

	void PushValue(unsigned int category, USER_DATA_TYPE type, void* value);
	void* GetValueByCategory(unsigned int category);

protected:
  struct UserData
	{
		unsigned int	category;
		USER_DATA_TYPE		type;
		void*				value;
	};

	std::vector<UserData> m_vUserDatas;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComUserData);
};

}; // namespace magicland

#endif // ML_ENTITYCOMONENT_MLCOMUSERDATA_H_