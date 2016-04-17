#include "entitycomponent/ml_component.h"

#include "marco.h"
#include "entitycomponent/ml_entity.h"

using namespace magicland;

MLComponent::MLComponent(MLComType type, MLEntity* entity)
	:m_Type(type)
	,m_Entity(entity) {
	ML_SAFE_ASSERT(entity != NULL, "Entity can not be null");
	ML_SAFE_GRAB(entity); // Add the reference count
}

MLComponent::~MLComponent() {
	ML_SAFE_DROP(m_Entity);
}

MLComType MLComponent::GetType() const {
	return m_Type;
}