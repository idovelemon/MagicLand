//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/02
// Version: 1.0
// Breif: This file will define the entity interface. All the entity in the
// game will inherit from this interface.
// Update: 2015/12/5 - Use Entity-Component architecture to refract the entity
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLENTITY_H_
#define ML_ENTITYCOMPONENT_MLENTITY_H_

#include <map>

#include "marco.h"
#include "entitycomponent/ml_component.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLRoom;

enum MLEntityMainType
{
	ML_ETYMAINTYPE_NONE = -1,	
	ML_ETYMAINTYPE_ENV,		// This indicate the environment main type. This kind of entity can not be destroy by player.
	ML_ETYMAINTYPE_PLAYER,	// This indicate the player main type.All entity in this kind will belong to player
	ML_ETYMAINTYPE_PLAYER_MAGIC, // This indicate the magic of the player
	ML_ETYMAINTYPE_ENEMY,	// This indicate the enemy main type.
	ML_ETYMAINTYPE_ENEMYMAGIC, // This indicate the enemy's magic type

	ML_ETYMAINTYPE_TOTAL,	// This indicate how many entity main type in magicland
};

enum MLEntitySubType
{
	ML_ETYSUBTYPE_NONE = -1,
	ML_ETYSUBTYPE_EMPTY,	// This indicate the empty area in the game
	ML_ETYSUBTYPE_WALL,		// This indicate the wall in the game
	ML_ETYSUBTYPE_XJ,		// This indicate the hero xj in the game
	ML_ETYSUBTYPE_ORGE,		// This indicate the enemy orge in the game
	ML_ETYSUBTYPE_JUMPORGE, // This indicate the jump orge in the game
	ML_ETYSUBTYPE_MOVEPLATFORM,
	ML_ETYSUBTYPE_THROWORGE,
	ML_ETYSUBTYPE_GEARCORE,

	ML_ETYSUBTYPE_TERRIAN,	// This indicate the terrian boundbox in the game
	ML_ETYSUBTYPE_FIREBALL, // This indicate the fire ball in the game
	ML_ETYSUBTYPE_BOOMBALL, 
	ML_ETYSUBTYPE_BROKENSTONE,

	ML_ETYSUBTYPE_TOTAL,	// This indicate how many entity type in magicland
};

enum MLDir
{
	ML_DIR_UP, 
	ML_DIR_LEFT,
	ML_DIR_DOWN,
	ML_DIR_RIGHT
};

class MLEntity:public MLReference {
public:
	MLEntity(MLEntityMainType main, MLEntitySubType sub, MLRoom* room);
	virtual ~MLEntity();

	//---------------------------------------------------------------------
	// Desc:This method will add the component into the entity.Entity can only
	// hold one component of one type.
	// Param:[in] com The component that need to be added into the entity
	//---------------------------------------------------------------------
	virtual void AddComponent(MLComponent* com);

	//---------------------------------------------------------------------
	// Desc: This method must be called when you want to destroy the entity.
	// You must destroy all the component of the entity, then you can destroy the entity
	//---------------------------------------------------------------------
	virtual void RemoveAllComponents();

	//---------------------------------------------------------------------
	// Desc:This method will get the specific component of the entity.If the
	// specific component do not exsit, the method will return NULL
	// Param:[in] type The type of the component that need to be return
	// Ret: If success, return the component; otherwise return NULL
	//---------------------------------------------------------------------
	virtual MLComponent* GetComponent(MLComType type);

	//---------------------------------------------------------------------
	// Desc:These method deal with the lifetime of the entity.When the IsEntityDead
	// return the true.It indicate that this entity must be destroyed.
	//---------------------------------------------------------------------
	virtual bool IsEntityDead();
	virtual void KillEntity();

	//---------------------------------------------------------------------
	// Desc: Get the id of this entity
	// Ret: return the id of the entity
	//---------------------------------------------------------------------
	virtual unsigned int GetID() const;

	//---------------------------------------------------------------------
	// Desc: Get the main type of the entity
	// Ret: Return the main type of the entity
	//---------------------------------------------------------------------
	virtual MLEntityMainType GetMainType() const;

	//---------------------------------------------------------------------
	// Desc: Get the sub type of the entity
	// Ret: Return the sub type of the entity
	//---------------------------------------------------------------------
	virtual MLEntitySubType GetSubType() const;

	//---------------------------------------------------------------------
	// Desc: Get the room which hold the entity
	// Ret: Return the room hold the entity
	//---------------------------------------------------------------------
	virtual MLRoom* GetRoom() const;

protected:
	typedef std::map<MLComType, MLComponent*> MLComponentTable;
	typedef std::map<MLComType, MLComponent*>::iterator MLComponentTableIt;
	MLComponentTable    m_ComponentTable;		// Store all the component of this entity

	bool				m_IsEntityDead;			// Indicate if the entity is dead
	unsigned int		m_ID;					// The id of the entity
	MLEntityMainType	m_MainType;				// The entity's main type include player, enemy, environment
	MLEntitySubType		m_SubType;				// The entity's sub type include such like wall,ground,tree,spike and so on
	MLRoom*				m_Room;					// The room that hold the entity
	static unsigned int s_IDGenerator;			// The static ID generator

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLEntity);
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLENTITY_H_