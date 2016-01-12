#include "MLComUserData.h"

using namespace MagicLand;

MLComUserData::MLComUserData(MagicLand::MLEntity* entity)
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

void* MLComUserData::GetValueByCategory(USER_DATA_CATEGORY category)
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

