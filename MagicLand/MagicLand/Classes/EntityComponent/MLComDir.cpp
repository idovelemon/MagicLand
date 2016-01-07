#include "MLComDir.h"
using namespace MagicLand;

MLComDir::MLComDir(MLEntity* entity, MLDir dir)
	:MLComponent(ML_COMTYPE_DIR, entity)
	,m_Dir(dir)
{
}

MLComDir::~MLComDir()
{
}

void MLComDir::SetDir(MLDir dir)
{
	m_Dir = dir;
}

MLDir MLComDir::GetDir()
{
	return m_Dir;
}