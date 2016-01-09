#include "MLScriptMgr.h"
#include "../../marco.h"

MLScriptMgr* MLScriptMgr::s_Instance = NULL;

MLScriptMgr::MLScriptMgr()
{
}

MLScriptMgr::~MLScriptMgr()
{
	ML_SAFE_DELETE(s_Instance);
}

MLScriptMgr* MLScriptMgr::SharedInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new MLScriptMgr;
	}

	ML_SAFE_ASSERT(s_Instance, "Error: MLScriptMgr instance is null.");

	return s_Instance;
}

void MLScriptMgr::LoadScript(const char* scriptFile)
{
	ifstream file(scriptFile);

	ML_SAFE_ASSERT(file, "Error: MLScriptMgr file is null");

	MLKeyValuePair keyValue;
	char* split = " =";
	char* tip = "#";
	string line;

	while (!file.eof())
	{
		char* buffer = (char*) malloc(sizeof(char) * line.length());
		getline(file, line);
		strcpy(buffer, line.data());

		keyValue.segment = strtok(buffer, split);
		keyValue.value = atof(strtok(NULL, split));

		m_KeyValueArray.push_back(keyValue);
	}

	file.close();
}

float MLScriptMgr::GetValue(const char* segment)
{
	vector<MLKeyValuePair>::iterator it = m_KeyValueArray.begin();
	
	while (it != m_KeyValueArray.end())
	{
		if (strcmp((*it).segment, segment) == 0)
		{
			break;
		}

		it++;
	}

	return (*it).value;
}


