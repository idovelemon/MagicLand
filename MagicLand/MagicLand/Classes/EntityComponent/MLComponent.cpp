#include "MLComponent.h"
#include "MLEntity.h"
#include "../marco.h"
using namespace MagicLand;

MLComponent::MLComponent(MLComType type, MLEntity* pEntity)
	:m_Type(type)
	,m_Entity(pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Entity can not be null");
	m_Entity->Grab(); // Add the reference count
}

MLComponent::~MLComponent()
{
}

MLComType MLComponent::GetType() const
{
	return m_Type;
}