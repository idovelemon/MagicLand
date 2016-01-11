#include "MLEntityCreator.h"
#include "../marco.h"
#include "MLAllComs.h"
#include "../StateMachine/MLStartState.h"
#include "MLComOrgeWalkRange.h"
#include "../Support/Script/MLScriptMgr.h"
using namespace MagicLand;

MLETYCreatorEntry MLEntityCreator::s_CreatorTable[] = 
{
	{ML_ETYSUBTYPE_WALL, &MLEntityCreator::CreateWall},
	{ML_ETYSUBTYPE_XJ, &MLEntityCreator::CreateXJ},
	{ML_ETYSUBTYPE_ORGE, &MLEntityCreator::CreateOrge},
	{ML_ETYSUBTYPE_JUMPORGE, &MLEntityCreator::CreateJumpOrge},
};

MLEntity* MLEntityCreator::CreateEntity(MLEntitySubType type, int xCoord, int yCoord, MLRoom* room)
{
	ML_SAFE_ASSERT(ML_ETYSUBTYPE_NONE < type && type < ML_ETYSUBTYPE_TOTAL, "Please make sure the type is correctly");

	int size = sizeof(s_CreatorTable) / sizeof(MLETYCreatorEntry);

	MLEntity* entity = NULL;
	for(int i = 0; i < size; i++)
	{
		if(type == s_CreatorTable[i].type)
		{
			entity = s_CreatorTable[i].creator(xCoord, yCoord, room);
			break;
		}
	}

	ML_SAFE_ASSERT(entity != NULL, "Can not find the creator for this type,please make sure the creator is in s_CreatorTable");

	return entity;
}

MLEntity* MLEntityCreator::CreateTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room)
{
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

MLEntity* MLEntityCreator::CreateWall(int xCoord, int yCoord, MLRoom* room)
{
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

MLEntity* MLEntityCreator::CreateXJ(int xCoord, int yCoord, MLRoom* room)
{
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

MLEntity* MLEntityCreator::CreateOrge(int xCoord, int yCoord, MLRoom* room)
{
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateOrge((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateJumpOrge(int xCoord, int yCoord, MLRoom* room)
{
	ML_SAFE_ASSERT(room != NULL, "Please make sure the room is not empty");
	room->TransformMapCoordToWorldCoord(xCoord, yCoord);

	return CreateJumpOrge((float)xCoord, (float)yCoord, room);
}

MLEntity* MLEntityCreator::CreateFireBall(float posx, float posy, MLDir dir, MLRoom* room)
{
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
	if(dir == ML_DIR_LEFT)
	{
		movement->SetVel(-moveSpeed, 0.0f);
	}
	else if(dir == ML_DIR_RIGHT)
	{
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

MLEntity* MLEntityCreator::CreateOrge(float posx, float posy, MLRoom* room)
{
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

	// Create OrgeWalkRange component
	float range = MLScriptMgr::SharedInstance()->GetValue("OrgeMoveRange");
	MLComOrgeWalkRange* orgeWalkRange = new MLComOrgeWalkRange(entity, posx, range);
	ML_SAFE_ASSERT(orgeWalkRange != NULL, "Failed to create OrgeWalkRange component");
	entity->AddComponent(orgeWalkRange);
	ML_SAFE_DROP(orgeWalkRange);

	return entity;
}

MLEntity* MLEntityCreator::CreateJumpOrge(float posx, float posy, MLRoom* room)
{
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

	return entity;
}