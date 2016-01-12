//---------------------------------------------------------
// Declaration: Copyright (c) 2016. All right reserved.
// Author:
// Date: 2016 / 01 / 12
// Version: 1.0
// Brief:
//---------------------------------------------------------
#ifndef __MLCOMUSERDATA_H__
#define __MLCOMUSERDATA_H__

#include <vector>

#include "MLEntity.h"
#include "MLComponent.h"

using namespace std;

namespace MagicLand
{
	class MLComUserData;
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

		USER_DATA_TYPE_MAX
	};

	enum USER_DATA_CATEGORY
	{
		USER_DATA_CATEGORY_ORIGIN,

		USER_DATA_CATEGORY_MAX
	};

	struct UserData
	{
		USER_DATA_CATEGORY	category;
		USER_DATA_TYPE		type;
		void*				value;
	};

public:
	void PushValue(UserData userData);

	void* GetValueByCategory(USER_DATA_CATEGORY category);

protected:
	vector<UserData> m_vUserDatas;
};

#endif