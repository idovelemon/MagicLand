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

#include "ml_component.h"

using namespace std;

namespace MagicLand
{
	class MLComUserData;
	class MLEntity;
};

class MagicLand::MLComUserData
	: public MagicLand::MLComponent
{
public:
	MLComUserData(MagicLand::MLEntity* entity);
	virtual ~MLComUserData();

public:
	enum USER_DATA_TYPE
	{
		USER_DATA_TYPE_INTEGER,
		USER_DATA_TYPE_FLOAT,
		USER_DATA_TYPE_POINTER,

		USER_DATA_TYPE_MAX
	};

private:
	struct UserData
	{
		unsigned int	category;
		USER_DATA_TYPE		type;
		void*				value;
	};

public:
	void PushValue(unsigned int category, USER_DATA_TYPE type, void* value);

	void* GetValueByCategory(unsigned int category);

protected:
	vector<UserData> m_vUserDatas;
};

#endif // ML_ENTITYCOMONENT_MLCOMUSERDATA_H_