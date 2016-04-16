#include "ml_scriptmgr.h"

#include "../../marco.h"

MLScriptMgr* MLScriptMgr::s_Instance = NULL;

MLScriptMgr::MLScriptMgr()
{
}

MLScriptMgr::~MLScriptMgr()
{
	vector<MLKeyValuePair>::iterator it = m_KeyValueArray.begin();
	
	while (it != m_KeyValueArray.end())
	{
		char* buffer = it->segment;
		ML_SAFE_DELETE_ARRAY(buffer);
		++it;
	}

	m_KeyValueArray.clear();
}

MLScriptMgr* MLScriptMgr::SharedInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new MLScriptMgr;
	}

	ML_SAFE_ASSERT(s_Instance != NULL, "Error: MLScriptMgr instance is null.");

	return s_Instance;
}

void MLScriptMgr::LoadScript(const char* scriptFile)
{
	ifstream file(scriptFile);

	ML_SAFE_ASSERT(!file.fail(), "Error: MLScriptMgr file is null");

	MLKeyValuePair keyValue;
	char* split = " =\"\'";
	char* tip = "#";
	string line;

	while (!file.eof())
	{
		getline(file, line);
		line = line.substr(0, line.find("#"));

		if (line == "")
		{
			continue;
		}

		char buffer[256];
		strcpy(buffer, line.data());
		strtok(buffer, split);

		if (strcmp(buffer, "import") == 0
			|| strcmp(buffer, "include") == 0)
		{
			char str[256] = {"Script/"};
			LoadScript(strcat(str, strtok(NULL, split)));
		}
		else
		{
			int length = strlen(buffer);
			keyValue.segment = new char[length + 1];
			keyValue.segment[length] = '\0';
			memcpy(keyValue.segment, buffer, length);
			keyValue.value = atof(strtok(NULL, split));
			m_KeyValueArray.push_back(keyValue);
		}
	}

	file.close();
}

float MLScriptMgr::GetValue(const char* segment)
{
	vector<MLKeyValuePair>::iterator it = m_KeyValueArray.begin();
	bool flag = false;
	
	while (it != m_KeyValueArray.end())
	{
		if (strcmp((*it).segment, segment) == 0)
		{
			flag = true;
			break;
		}

		it++;
	}

	if (!flag)
	{
		ML_SAFE_ASSERT(NULL, "Error: MLScriptMgr find result was not found");
	}

	return (*it).value;
}

void MLScriptMgr::Destory()
{
	ML_SAFE_DELETE(s_Instance);
}