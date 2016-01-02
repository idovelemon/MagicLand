//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/11/29
// Version:1.0
// Brief: This file will define the room interface.A round has many rooms.
//        Player will explore and combat at a room.
//------------------------------------------------------------------------
#ifndef __MLROOM__H_
#define __MLROOM__H_

#include "cocos2d.h"
#include "../Reference/MLReference.h"
#include "../Camera/MLCamera.h"
#include "../Support/XJMath/XJMath.h"
using namespace cocos2d;

namespace MagicLand{ class MLRoom;};

class MagicLand::MLRoom:public MLReference
{
public:
    MLRoom();
    virtual ~MLRoom();

    // setter and getter
public:
	void SetScene(CCScene* scene);
	CCScene* GetScene() const;

	void SetBackground(CCSprite* background);
	CCSprite* GetBackground() const;

	void SetGameLayer(CCLayer* layer);
	CCLayer* GetGameLayer() const;

	void SetCamera(MLCamera* camera);
	MLCamera* GetCamera() const;

	void SetRoomHeight(int height);
	int GetRoomHeight() const;

	void SetRoomWidth(int width);
	int GetRoomWidth() const;

	void SetTileWidth(int width);
	int GetTileWidth() const;

	void SetTileHeight(int height);
	int GetTileHeight() const;

	void CopyRoomMap(const char* map);
	char* GetRoomMap() const;

	char GetGridType(int x, int y);

	//------------------------------------------------------------------------
	// Desc: This method will transform the coordinate of the map into
	// world's position
	// Param:[in-out] x in_x indicate the coordinate in the map
	//					out_x indicate the coordinate in the world
	// Param:[in-out] y in_y indicate the coordinate in the map
	//					out_y indicate the coordinate in the world
	//------------------------------------------------------------------------
	void TransformMapCoordToWorldCoord(int& x, int& y);

	void AddTerrianBoundBox(VECTOR2 min, VECTOR2 max);
	int GetTerrianNum() const;
	void GetTerrianAt(int index, VECTOR2& min, VECTOR2& max);

public:
	virtual bool Init();
	virtual void Update(float delta);
	virtual void Destroy();

protected:
	CCScene*	m_Scene;        // The scene of this room
	CCSprite*	m_Background;   // The background sprite
	CCLayer*	m_GameLayer;	// The game layer which hold all the game's sprite
	MLCamera*	m_Camera;       // The camera to look at this room
	int			m_TileWidth;    // The tile's width
	int			m_TileHeight;   // The tile's height
	int			m_RoomHeight;   // The room's height
	int			m_RoomWidth;    // The room's width
	char*		m_RoomMap;      // The room's map
	
	struct TerrianBoundBox
	{
		VECTOR2 min;
		VECTOR2 max;
	};

	std::vector<TerrianBoundBox> m_Terrians; // The vector hold all the terrian's bound box
};
#endif