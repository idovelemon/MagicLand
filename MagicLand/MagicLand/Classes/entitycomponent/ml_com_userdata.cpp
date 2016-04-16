#include "entitycomponent/ml_com_userdata.h"

#include "marco.h"
#include "entitycomponent/ml_entity.h"

using namespace MagicLand;

MLComUserData::MLComUserData(MagicLand::MLEntity* entity)
	: MLComponent(ML_COMTYPE_USERDATA, entity)
{
}

MLComUserData::~MLComUserData()
{
	for (vector<UserData>::iterator it = m_vUserDatas.begin();
			it != m_vUserDatas.end();
			++it)
	{
		switch (it->type)
		{
		case USER_DATA_TYPE_INTEGER:
		case USER_DATA_TYPE_FLOAT:
			break;

		case USER_DATA_TYPE_POINTER:
			ML_SAFE_DELETE(it->value);
			break;

		default:
			break;
		}
	}

	m_vUserDatas.clear();
}

void MLComUserData::PushValue(unsigned int category, USER_DATA_TYPE type, void* value)
{
	UserData userData;
	userData.category = category;
	userData.type = type;
	userData.value = value;
	m_vUserDatas.push_back(userData);
}

void* MLComUserData::GetValueByCategory(unsigned int category)
{
	for (vector<UserData>::iterator it = m_vUserDatas.begin();
			it != m_vUserDatas.end();
			++it)
	{
		if (category == it->category)
		{
			return it->value;
		}
	}

	return NULL;
}

