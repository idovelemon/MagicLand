#include "entitycomponent/ml_entitycreator.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"
#include "stateMachine/ml_startstate.h"
#include "support/script/ml_scriptmgr.h"
#include "round/ml_room.h"

using namespace cocos2d;
using namespace magicland;

MLETYCreatorEntry MLEntityCreator::s_CreatorTable[] = {
	{ML_ETYSUBTYPE_WALL, &MLEntityCreator::CreateWall},
	{ML_ETYSUBTYPE_XJ, &MLEntityCreator::CreateXJ},
	{ML_ETYSUBTYPE_ORGE, &MLEntityCreator::CreateOrge},
	{ML_ETYSUBTYPE_JUMPORGE, &MLEntityCreator::CreateJumpOrge},
	{ML_ETYSUBTYPE_MOVEPLATFORM, &MLEntityCreator::CreateMovePlatform},
	{ML_ETYSUBTYPE_THROWORGE, &MLEntityCreator::CreateThrowOrge},
	{ML_ETYSUBTYPE_GEARCORE, &MLEntityCreator::CreateGearCore},
};

MLEntity* MLEntityCreator::CreateEntity(MLEntitySubType type, int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(ML_ETYSUBTYPE_NONE < type && type < ML_ETYSUBTYPE_TOTAL, "Please make sure the type is correctly");

	int size = sizeof(s_CreatorTable) / sizeof(MLETYCreatorEntry);

	MLEntity* entity = NULL;
	for (int i = 0; i < size; i++) {
		if (type == s_CreatorTable[i].type) {
			entity = s_CreatorTable[i].creator(xCoord, yCoord, room);
			break;
		}
	}

	ML_SAFE_ASSERT(entity != NULL, "Can not find the creator for this type,please make sure the creator is in s_CreatorTable");

	return entity;
}

MLEntity* MLEntityCreator::CreateTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "The pointer to room can not be null");

	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENV, ML_ETYSUBTYPE_TERRIAN, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");

	int cx = min.x, cy = min.y;
	room->TransformMapCoordToWorldCoord(cx, cy);
	min.x = cx; min.y = cy;

	cx = max.x; cy = max.y;
	room->TransformMapCoordToWorldCoord(cx, cy);
	max.x = cx; max.y = cy;

	cx = (max.x + min.x) * 0.5f;
	cy = (max.y + min.y) * 0.5f;

	// Create transform component
	MLComTransform* pTransform = new MLComTransform(entity, cx, cy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(pTransform != NULL, "Failed to create transform component");
	entity->AddComponent(pTransform);
	ML_SAFE_DROP(pTransform);

	float tileWidth = room->GetTileWidth();
	float tileHeight = room->GetTileHeight();
	float boundBoxWidth = max.x - min.x + tileWidth;
	float boundBoxHeight = min.y - max.y + tileHeight; // Warn: The map's coordinate is opposite to cocos2d's coordinate in y-axis

	// Create the boundbox component
	MLComBoundBox* pBoundBox = new MLComBoundBox(entity, boundBoxWidth, boundBoxHeight, cx, cy);
	ML_SAFE_ASSERT(pBoundBox != NULL, "Failed to create boundbox component");
	entity->AddComponent(pBoundBox);
	ML_SAFE_DROP(pBoundBox);

	return entity;
}

MLEntity* MLEntityCreator::CreateWall(int xCoord, int yCoord, MLRoom* room) {
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENV, ML_ETYSUBTYPE_WALL, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to allocate memory for entity");

	// Create display component
	MLComDisplay* display = new MLComDisplay(entity, "Wall.png", room->GetGameLayer());
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(xCoord * 1.0f, yCoord * 1.0f));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	return entity;
}

MLEntity* MLEntityCreator::CreateXJ(int xCoord, int yCoord, MLRoom* room) {
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_PLAYER, ML_ETYSUBTYPE_XJ, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to allocate memory for entity");

	// Create display component
	MLComDisplay* display = new MLComDisplay(entity, "TestRole.png", room->GetGameLayer());
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(xCoord * 1.0f, yCoord * 1.0f));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create the transform component
	MLComTransform* transform = new MLComTransform(entity, xCoord, yCoord, 1.0f, 1.0f, 0.0f);
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create the boundbox component
	float boundWidth = MLScriptMgr::SharedInstance()->GetValue("HeroXJBoundBoxWidth");
	float boundHeight = MLScriptMgr::SharedInstance()->GetValue("HeroXJBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, boundWidth, boundHeight, xCoord, yCoord);
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create the state component
	MLComState* state = new MLComState(entity);
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	// Create the movement component
	float gravity = MLScriptMgr::SharedInstance()->GetValue("HeroXJGravity");
	float maxFallSpeed = MLScriptMgr::SharedInstance()->GetValue("HeroXJMaxFallSpeed");
	MLComMovement* movement = new MLComMovement(entity);
	movement->SetVel(0.0f, 0.0f);
	movement->SetGravity(gravity);
	movement->SetMaxFallSpeed(maxFallSpeed);
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create the dir component
	MLComDir* dir = new MLComDir(entity, ML_DIR_RIGHT);
	ML_SAFE_ASSERT(dir != NULL, "Create Dir component failed");
	entity->AddComponent(dir);
	ML_SAFE_DROP(dir);

	return entity;
}

MLEntity* MLEntityCreator::CreateOrge(int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateOrge((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateJumpOrge(int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateJumpOrge((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateMovePlatform(int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateMovePlatform((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateThrowOrge(int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateThrowOrge((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateGearCore(int xCoord, int yCoord, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	
	MLEntity* entity = NULL;
	if (room != NULL) {
		room->TransformMapCoordToWorldCoord(xCoord, yCoord);
		entity = CreateGearCore((float)xCoord, (float)yCoord, room);
	}

	return entity;
}

MLEntity* MLEntityCreator::CreateFireBall(float posx, float posy, MLDir dir, MLRoom* room) {
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_PLAYER_MAGIC, ML_ETYSUBTYPE_FIREBALL, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to allocate memory for entity");

	// Create display component
	MLComDisplay* display = new MLComDisplay(entity, "FireBall.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Create Display component failed");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Create Transform component failed");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create boundbox component
	float fireBallBoxWidth = MLScriptMgr::SharedInstance()->GetValue("FireBallBoundBoxWidth");
	float fireBallBoxHeight = MLScriptMgr::SharedInstance()->GetValue("FireBallBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, fireBallBoxWidth, fireBallBoxHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Create BoundBox component failed");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create movement component
	MLComMovement* movement = new MLComMovement(entity);
	movement->SetGravity(0.0f);
	movement->SetMaxFallSpeed(0.0f);
	float moveSpeed = MLScriptMgr::SharedInstance()->GetValue("FireBallMoveSpeed");
	if (dir == ML_DIR_LEFT) {
		movement->SetVel(-moveSpeed, 0.0f);
	} else if(dir == ML_DIR_RIGHT) {
		movement->SetVel(moveSpeed, 0.0f);
	}
	ML_SAFE_ASSERT(movement != NULL, "Create Movement component failed");
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create the state component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Create State component failed");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	// Create the timer component
	MLComTimer* timer = new MLComTimer(entity);
	ML_SAFE_ASSERT(timer != NULL, "Create Timer component failed");
	entity->AddComponent(timer);
	ML_SAFE_DROP(timer);

	return entity;
}

MLEntity* MLEntityCreator::CreateOrge(float posx, float posy, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");

	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENEMY, ML_ETYSUBTYPE_ORGE, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "TestEnemy.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create BoundBox component
	float orgeBoundBoxWidth = MLScriptMgr::SharedInstance()->GetValue("OrgeBoundBoxWidth");
	float orgeBoundBoxHeight = MLScriptMgr::SharedInstance()->GetValue("OrgeBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, orgeBoundBoxWidth, orgeBoundBoxHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(MLStartState::SharedInstance());
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	// Create Dir component
	MLComDir* dir = new MLComDir(entity, ML_DIR_RIGHT);
	ML_SAFE_ASSERT(dir != NULL, "Failed to create Dir component");
	entity->AddComponent(dir);
	ML_SAFE_DROP(dir);

	// Create Timer component
	MLComTimer* timer = new MLComTimer(entity);
	ML_SAFE_ASSERT(timer != NULL, "Failed to create Timer component");
	timer->AddTimer(ML_TIMER_FLAG_ORGE_WALK);
	timer->AddTimer(ML_TIMER_FLAG_ORGE_WAIT);
	entity->AddComponent(timer);
	ML_SAFE_DROP(timer);

	// Create UserData component
	float range = MLScriptMgr::SharedInstance()->GetValue("OrgeMoveRange");
	MLComUserData* userData = new MLComUserData(entity);
	ML_SAFE_ASSERT(userData != NULL, "Failed to create UserData component");

	float* pValueCenterX = new float;
	*pValueCenterX = posx;
	userData->PushValue(ML_USERDATA_FLAG_ORGE_CENTERX, MLComUserData::USER_DATA_TYPE_POINTER, pValueCenterX);

	float* pValueRange = new float;
	*pValueRange = range;
	userData->PushValue(ML_USERDATA_FLAG_ORGE_RANGE, MLComUserData::USER_DATA_TYPE_POINTER, pValueRange);

	entity->AddComponent(userData);
	ML_SAFE_DROP(userData);

	return entity;
}

MLEntity* MLEntityCreator::CreateJumpOrge(float posx, float posy, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");

	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENEMY, ML_ETYSUBTYPE_JUMPORGE, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "JumpOrge.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create BoundBox component
	float orgeBoundBoxWidth = MLScriptMgr::SharedInstance()->GetValue("JumpOrgeBoundBoxWidth");
	float orgeBoundBoxHeight = MLScriptMgr::SharedInstance()->GetValue("JumpOrgeBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, orgeBoundBoxWidth, orgeBoundBoxHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(MLStartState::SharedInstance());
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	// Create Dir component
	MLComDir* dir = new MLComDir(entity, ML_DIR_RIGHT);
	ML_SAFE_ASSERT(dir != NULL, "Failed to create Dir component");
	entity->AddComponent(dir);
	ML_SAFE_DROP(dir);

	// Create Movement component
	MLComMovement* movement = new MLComMovement(entity);
	ML_SAFE_ASSERT(movement != NULL, "Failed to create Movement component");
	movement->SetGravity(MLScriptMgr::SharedInstance()->GetValue("JumpOrgeGravity"));
	movement->SetMaxFallSpeed(MLScriptMgr::SharedInstance()->GetValue("JumpOrgeMaxFallSpeed"));
	movement->SetVel(0.0f, 0.0f);
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create UserData component
	MLComUserData* userData = new MLComUserData(entity);
	ML_SAFE_ASSERT(userData != NULL, "Failed to create UserData component");
	VECTOR2* pPos = new VECTOR2();
	pPos->x = posx;
	pPos->y = posy;
	userData->PushValue(ML_USERDATA_FLAG_JUMPORGE_INITPOS, MLComUserData::USER_DATA_TYPE_POINTER, pPos);
	entity->AddComponent(userData);
	ML_SAFE_DROP(userData);

	return entity;
}

MLEntity* MLEntityCreator::CreateMovePlatform(float posx, float posy, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");

	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENV, ML_ETYSUBTYPE_MOVEPLATFORM, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "MovePlatform.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create Movement component
	MLComMovement* movement = new MLComMovement(entity);
	ML_SAFE_ASSERT(movement != NULL, "Failed to create Movement component");
	movement->SetGravity(0.0f);
	movement->SetMaxFallSpeed(0.0f);
	float moveSpeed = MLScriptMgr::SharedInstance()->GetValue("MovePlatformMoveSpeed");
	movement->SetVel(moveSpeed, 0.0f); // Default to move right
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create Dir component
	MLComDir* dir = new MLComDir(entity, ML_DIR_RIGHT);
	ML_SAFE_ASSERT(dir != NULL, "Failed to create Dir component");
	entity->AddComponent(dir);
	ML_SAFE_DROP(dir);

	// Create BoundBox component
	float boundWidth = MLScriptMgr::SharedInstance()->GetValue("MovePlatformBoundBoxWidth");
	float boundHeight = MLScriptMgr::SharedInstance()->GetValue("MovePlatformBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, boundWidth, boundHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create UserData component
	MLComUserData* userData = new MLComUserData(entity);
	ML_SAFE_ASSERT(userData != NULL, "Failed to create UserData component");
	float* pInitPosX = new float;
	*pInitPosX = posx;
	userData->PushValue(ML_USERDATA_FLAG_MOVEPLATFORM_INITPOS, MLComUserData::USER_DATA_TYPE_POINTER, pInitPosX);

	float* pWidth = new float;
	*pWidth = MLScriptMgr::SharedInstance()->GetValue("MovePlatformMoveWidth");
	userData->PushValue(ML_USERDATA_FLAG_MOVEPLATFORM_WIDTH, MLComUserData::USER_DATA_TYPE_POINTER, pWidth);

	float* pDiff = new float;
	*pDiff = 0;
	userData->PushValue(ML_USERDATA_FLAG_MOVEPLATFORM_DIFF, MLComUserData::USER_DATA_TYPE_POINTER, pDiff);

	entity->AddComponent(userData);
	ML_SAFE_DROP(userData);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	ML_SAFE_DROP(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(state);

	return entity;
}

MLEntity* MLEntityCreator::CreateThrowOrge(float posx, float posy, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENEMY, ML_ETYSUBTYPE_THROWORGE, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create Entity");

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "ThrowOrge.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create BoundBox component
	float boxWidth = MLScriptMgr::SharedInstance()->GetValue("ThrowOrgeBoundBoxWidth");
	float boxHeight = MLScriptMgr::SharedInstance()->GetValue("ThrowOrgeBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, boxWidth, boxHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create UserData component
	MLComUserData* userData = new MLComUserData(entity);
	ML_SAFE_ASSERT(userData != NULL, "Failed to create UserData component");
	float* pThrowDelta = new float;
	*pThrowDelta = MLScriptMgr::SharedInstance()->GetValue("ThrowOrgeThrowDelta");
	userData->PushValue(ML_USERDATA_FLAG_THROWORGE_THROWDELTA, MLComUserData::USER_DATA_TYPE_POINTER, pThrowDelta);
	entity->AddComponent(userData);
	ML_SAFE_DROP(userData);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	// Create Timer component
	MLComTimer* timer = new MLComTimer(entity);
	ML_SAFE_ASSERT(timer != NULL, "Failed to create Timer component");
	timer->AddTimer(ML_TIMER_FLAG_THROWORGE_THROW);
	entity->AddComponent(timer);
	ML_SAFE_DROP(timer);

	return entity;
}

MLEntity* MLEntityCreator::CreateBoomBall(float posx, float posy, MLRoom* room) {
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENEMYMAGIC, ML_ETYSUBTYPE_BOOMBALL, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create Entity");

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "BoomBall.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create Movement component
	MLComMovement* movement = new MLComMovement(entity);
	ML_SAFE_ASSERT(movement != NULL, "Failed to create Movement component");
	movement->SetGravity(MLScriptMgr::SharedInstance()->GetValue("BoomBallGravity"));
	movement->SetMaxFallSpeed(MLScriptMgr::SharedInstance()->GetValue("BoomBallMaxFallSpeed"));
	movement->SetVel(0.0f, 0.0f);
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create BoundBox component
	float boxWidth = MLScriptMgr::SharedInstance()->GetValue("BoomBallBoundBoxWidth");
	float boxHeight = MLScriptMgr::SharedInstance()->GetValue("BoomBallBoundBoxHeight");
	MLComBoundBox* boundBox = new MLComBoundBox(entity, boxWidth, boxHeight, posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(state);
	ML_SAFE_DROP(startState);

	return entity;
}

MLEntity* MLEntityCreator::CreateBrokenStone(float posx, float posy, float velx, float vely, MLRoom* room) {
	MLEntity* entity = new MLEntity(ML_ETYMAINTYPE_ENEMYMAGIC, ML_ETYSUBTYPE_BROKENSTONE, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create Entity");

	// Create Display component
	MLComDisplay* display = new MLComDisplay(entity, "BrokenStone.png", room->GetGameLayer());
	ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
	display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
	display->GetSprite()->setPosition(ccp(posx, posy));
	entity->AddComponent(display);
	ML_SAFE_DROP(display);

	// Create Transform component
	MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
	ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
	entity->AddComponent(transform);
	ML_SAFE_DROP(transform);

	// Create Movement component
	MLComMovement* movement = new MLComMovement(entity);
	ML_SAFE_ASSERT(movement != NULL, "Failed to create Movement component");
	movement->SetGravity(MLScriptMgr::SharedInstance()->GetValue("BrokenStoneGravity"));
	movement->SetMaxFallSpeed(MLScriptMgr::SharedInstance()->GetValue("BrokenStoneMaxFallSpeed"));
	movement->SetVel(velx, vely);
	entity->AddComponent(movement);
	ML_SAFE_DROP(movement);

	// Create BoundBox component
	MLComBoundBox* boundBox = new MLComBoundBox(
      entity, 
		  MLScriptMgr::SharedInstance()->GetValue("BrokenStoneBoundBoxWidth"),
		  MLScriptMgr::SharedInstance()->GetValue("BrokenStoneBoundBoxWidth"),
		  posx, posy);
	ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
	entity->AddComponent(boundBox);
	ML_SAFE_DROP(boundBox);

	// Create State component
	MLComState* state = new MLComState(entity);
	ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
	MLStartState* startState = MLStartState::SharedInstance();
	state->SetState(startState);
	entity->AddComponent(state);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(state);

	return entity;
}

MLEntity* MLEntityCreator::CreateGearCore(float posx, float posy, MLRoom* room) {
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	MLEntity* entity = NULL;

	if (room != NULL) {
		entity = new MLEntity(ML_ETYMAINTYPE_ENEMY, ML_ETYSUBTYPE_GEARCORE, room);
		ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");
		if (entity != NULL) {

			// Create Display component
			MLComDisplay* display = new MLComDisplay(entity, "Image//Gear//gear_core.png", room->GetGameLayer());
			ML_SAFE_ASSERT(display != NULL, "Failed to create Display component");
			if (display != NULL) {
				CCSprite* sprite = display->GetSprite();
				ML_SAFE_ASSERT(sprite != NULL, "Sprite can not be empty");
				if (sprite != NULL) {
					sprite->setAnchorPoint(ccp(0.5f, 0.5f));
					sprite->setPosition(ccp(posx, posy));
				}

				entity->AddComponent(display);
				ML_SAFE_DROP(display);
			}

			// Create Transform component
			MLComTransform* transform = new MLComTransform(entity, posx, posy, 1.0f, 1.0f, 0.0f);
			ML_SAFE_ASSERT(transform != NULL, "Failed to create Transform component");
			if (transform != NULL) {
				entity->AddComponent(transform);
				ML_SAFE_DROP(transform);
			}

			// Create Movement component
			MLComMovement* movement = new MLComMovement(entity);
			ML_SAFE_ASSERT(movement != NULL, "Failed to create Movement component");
			if (movement != NULL) {
				movement->SetGravity(0.0f);
				movement->SetMaxFallSpeed(0.0f);
				movement->SetVel(0.0f, 0.0f);
				entity->AddComponent(movement);
				ML_SAFE_DROP(movement);
			}

			// Create BoundBox component
			MLComBoundBox* boundBox = new MLComBoundBox(
          entity, 
				  MLScriptMgr::SharedInstance()->GetValue("BrokenStoneBoundBoxWidth"),
				  MLScriptMgr::SharedInstance()->GetValue("BrokenStoneBoundBoxWidth"),
				  posx, posy);
			ML_SAFE_ASSERT(boundBox != NULL, "Failed to create BoundBox component");
			if (boundBox != NULL) {
				entity->AddComponent(boundBox);
				ML_SAFE_DROP(boundBox);
			}

			// Create State component
			MLComState* state = new MLComState(entity);
			ML_SAFE_ASSERT(state != NULL, "Failed to create State component");
			if (state != NULL) {
				MLStartState* startState = MLStartState::SharedInstance();
				state->SetState(startState);
				entity->AddComponent(state);
				ML_SAFE_DROP(startState);
				ML_SAFE_DROP(state);
			}
		}
	}

	return entity;
}