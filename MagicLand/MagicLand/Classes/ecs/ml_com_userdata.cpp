#include "ml_com_userdata.h"

#include "marco.h"
#include "ml_entity.h"

using namespace magicland;
using namespace std;

MLComUserData::MLComUserData(magicland::MLEntity* entity)
	: MLComponent(ML_COMTYPE_USERDATA, entity) {
}

MLComUserData::~MLComUserData() {
	for (vector<UserData>::iterator it = m_vUserDatas.begin();
			 it != m_vUserDatas.end();
			 ++it) {
		switch (it->type) {
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

void MLComUserData::PushValue(unsigned int tag, USER_DATA_TYPE type, void* value) {
	UserData userData;
	userData.tag = tag;
	userData.type = type;
	userData.value = value;
	m_vUserDatas.push_back(userData);
}

void* MLComUserData::GetValueByCategory(unsigned int tag) {
	for (vector<UserData>::iterator it = m_vUserDatas.begin();
			 it != m_vUserDatas.end();
			 ++it) {
		if (tag == it->tag) {
			return it->value;
		}
	}

	return NULL;
}

void MLComUserData::UpdateValue(unsigned int tag, void* value) {
  for (vector<UserData>::iterator it = m_vUserDatas.begin(); it != m_vUserDatas.end(); ++it) {
		if (tag == it->tag) {
      it->value = value;
		}
	}
}