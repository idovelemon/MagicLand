#include "MLComponent.h"

#include "../marco.h"
#include "MLEntity.h"

using namespace MagicLand;

MLComponent::MLComponent(MLComType type, MLEntity* entity)
	:m_Type(type)
	,m_Entity(entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Entity can not be null");
	ML_SAFE_GRAB(entity); // Add the reference count
}

MLComponent::~MLComponent()
{
	ML_SAFE_DROP(m_Entity);
}

MLComType MLComponent::GetType() const
{
	return m_Type;
}