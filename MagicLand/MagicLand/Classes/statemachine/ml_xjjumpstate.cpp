#include "statemachine/ml_xjjumpstate.h"

#include "marco.h"
#include "entitycomponent/ml_com_boundbox.h"
#include "entitycomponent/ml_com_display.h"
#include "entitycomponent/ml_com_movement.h"
#include "entitycomponent/ml_com_transform.h"
#include "statemachine/ml_statemethod.h"

using namespace magicland;

MLXJJumpState::MLXJJumpState() {
}

MLXJJumpState::~MLXJJumpState() {
}

void MLXJJumpState::Enter(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");
	if (entity != NULL) {
		MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");
		if (pMovement != NULL) {
			VECTOR2 vel = pMovement->GetVel();
			vel.y += 20.0f;
			pMovement->SetVel(vel.x, vel.y);
		}
	}
}

void MLXJJumpState::Run(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");
	if (entity != NULL) {
		Jump(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLXJJumpState::Exit(MLEntity* entity) {
}

void MLXJJumpState::OnCollision(MLEntity* entity) {
	MLStateMethod::OnCollision(entity);
}

void MLXJJumpState::Jump(magicland::MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");
	if (entity != NULL) {
		MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		if (pMovement != NULL && pTransform != NULL) {
			VECTOR2 vel = pMovement->GetVel();

			if (GetKeyState('A') & 0x8000) {
				vel.x -= 3.0f;
			} else if (GetKeyState('D') & 0x8000) {
				vel.x += 3.0f;
			}

			vel.y -= pMovement->GetGravity();

			VECTOR2 pos = pTransform->GetPos();
			Vec2Add(pos, pos, vel);

			pTransform->SetPos(pos.x, pos.y);

			// Only save the y-axis of the velocity
			pMovement->SetVel(0.0f, vel.y);
		}
	}
}