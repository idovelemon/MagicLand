#ifndef __MLSCRIPTMGR_H__
#define __MLSCRIPTMGR_H__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class MLScriptMgr
{
protected:
	MLScriptMgr();
	virtual ~MLScriptMgr();

public:
	static MLScriptMgr* SharedInstance();

public:
	void LoadScript(const char* scriptFile);
	float GetValue(const char* segment);
	void Destory();

protected:
	static MLScriptMgr* s_Instance;
	struct MLKeyValuePair
	{
		char* segment;
		float value;
	};

	vector<MLKeyValuePair> m_KeyValueArray;
};

// (2016 / 01 / 10 xiaojian)
#define ML_SCRIPT_GETVALUE(_store_, _segment_) \
	{\
		static float temp = MLScriptMgr::SharedInstance()->GetValue(_segment_);\
		_store_ = temp;\
	}

#endif  // __APP_DELEGATE_H__

