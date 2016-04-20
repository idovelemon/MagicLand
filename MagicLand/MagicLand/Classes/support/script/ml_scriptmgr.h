#ifndef ML_SCRIPT_MLSCRIPTMGR_H_
#define ML_SCRIPT_MLSCRIPTMGR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "marco.h"

class MLScriptMgr {
public:
	static MLScriptMgr* SharedInstance();

	void LoadScript(const char* scriptFile);
	float GetValue(const char* segment);
	void Destory();

protected:
  struct MLKeyValuePair {
		char* segment;
		float value;
	};

  MLScriptMgr();
	virtual ~MLScriptMgr();

	static MLScriptMgr* s_Instance;
	std::vector<MLKeyValuePair> m_KeyValueArray;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLScriptMgr);
};

// (2016 / 01 / 10 xiaojian)
#define ML_SCRIPT_GETVALUE(_store_, _segment_) {\
		static float temp = MLScriptMgr::SharedInstance()->GetValue(_segment_);\
		_store_ = temp;\
	}

#endif  // ML_SCRIPT_MLSCRIPTMGR_H_