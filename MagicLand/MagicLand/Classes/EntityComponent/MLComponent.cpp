#include "MLComponent.h"
#include "MLEntity.h"
#include "../marco.h"
using namespace MagicLand;

MLComponent::MLComponent(MLComType type, MLEntity* pEntity)
	:m_Type(type)
	,m_Entity(pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Entity can not be null");
	ML_SAFE_GRAB(pEntity); // Add the reference count
}

MLComponent::~MLComponent()
{
	ML_SAFE_DROP(m_Entity);
}

MLComType MLComponent::GetType() const
{
	return m_Type;
}