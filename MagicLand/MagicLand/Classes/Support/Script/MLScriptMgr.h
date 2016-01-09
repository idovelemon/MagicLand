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

protected:
	static MLScriptMgr* s_Instance;
	struct MLKeyValuePair
	{
		char* segment;
		float value;
	};

	vector<MLKeyValuePair> m_KeyValueArray;
};

#endif  // __APP_DELEGATE_H__

