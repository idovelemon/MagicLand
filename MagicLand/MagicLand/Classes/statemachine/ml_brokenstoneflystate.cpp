#include "statemachine/ml_brokenstoneflystate.h"

#include "marco.h"
#include "statemachine/ml_statemethod.h"
#include "entitycomponent/ml_allcoms.h"

using namespace magicland;

MLBrokenStoneFlyState::MLBrokenStoneFlyState() {
}

MLBrokenStoneFlyState::~MLBrokenStoneFlyState() {
}

void MLBrokenStoneFlyState::Enter(MLEntity* entity) {
}

void MLBrokenStoneFlyState::Run(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Entity can not be NULL");
	if (entity != NULL) {
		Fly(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLBrokenStoneFlyState::Exit(MLEntity* entity) {
}

void MLBrokenStoneFlyState::OnCollision(MLEntity* entity) {
}

void MLBrokenStoneFlyState::Fly(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if (entity != NULL) {
		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
		if (transform != NULL) {
			VECTOR2 pos = transform->GetPos();

			MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
			ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
			if (movement != NULL) {
				VECTOR2 vel = movement->GetVel();
				vel.y -= movement->GetGravity();

				if (vel.y <= -movement->GetMaxFallSpeed()) {
					vel.y = -movement->GetMaxFallSpeed();
				}

				Vec2Add(pos, pos, vel);

				transform->SetPos(pos.x, pos.y);
				movement->SetVel(vel.x, vel.y);
			}
		}
	}
}