#include "MLComUserData.h"
#include "../marco.h"

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

void MLComUserData::PushValue(UserData userData)
{
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

