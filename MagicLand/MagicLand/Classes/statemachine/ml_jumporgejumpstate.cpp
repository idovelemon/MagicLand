#include "statemachine/ml_jumporgejumpstate.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"
#include "entitycomponent/ml_entitymgr.h"
#include "statemachine/ml_statemethod.h"
#include "support/script/ml_scriptmgr.h"

using namespace magicland;

MLJumpOrgeJumpState::MLJumpOrgeJumpState() {
}

MLJumpOrgeJumpState::~MLJumpOrgeJumpState() {
}

void MLJumpOrgeJumpState::Enter(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if (entity != NULL) {
		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");

		MLEntity* player = MLEntityMgr::SharedInstance()->GetPlayer();
		ML_SAFE_ASSERT(player != NULL, "Please make sure the player is not empty");

		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");

		MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
		ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component is not empty");

		if (movement != NULL && player != NULL && transform != NULL && dir != NULL) {
			VECTOR2 pos = transform->GetPos();
			
			MLComTransform* playerTransform = (MLComTransform*)player->GetComponent(ML_COMTYPE_TRANSFORM);
			ML_SAFE_ASSERT(playerTransform != NULL, "Please make sure the Transform component is not empty");
			if (playerTransform != NULL) {
				VECTOR2 playerPos = playerTransform->GetPos();

				float moveSpeed = 0.0f, jumpSpeed = 0.0f;
				ML_SCRIPT_GETVALUE(moveSpeed, "JumpOrgeMoveSpeed");
				ML_SCRIPT_GETVALUE(jumpSpeed, "JumpOrgeJumpSpeed");
				
        // Player is at the left of the JumpOrge
        if (playerPos.x < pos.x) {
					movement->SetVel(-moveSpeed, jumpSpeed);
					dir->SetDir(ML_DIR_LEFT);
				} else	{				// Player is at the right of the JumpOrge
					movement->SetVel(moveSpeed, jumpSpeed);
					dir->SetDir(ML_DIR_RIGHT);
				}
			}
		}
	}
}

void MLJumpOrgeJumpState::Run(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if (entity != NULL) {
		Jump(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLJumpOrgeJumpState::Exit(MLEntity* entity) {
}

void MLJumpOrgeJumpState::OnCollision(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if (entity != NULL) {
		MLStateMethod::OnCollision(entity);
	}
}

void MLJumpOrgeJumpState::Jump(MLEntity* entity) {
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if (entity != NULL) {	
		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "There is no movement component");

		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "There is no transform component");

		if (movement != NULL && transform != NULL) {
			VECTOR2 vel = movement->GetVel();
			vel.y -= movement->GetGravity();
			if (vel.y < -movement->GetMaxFallSpeed()) {
				vel.y = -movement->GetMaxFallSpeed();
			}
			movement->SetVel(vel.x, vel.y);

			VECTOR2 pos = transform->GetPos();
			Vec2Add(pos, pos, vel);

			transform->SetPos(pos.x, pos.y);
		}
	}
}