//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/11/29
// Version:1.0
// Brief: This file will define the room interface.A round has many rooms.
//        Player will explore and combat at a room.
//------------------------------------------------------------------------
#ifndef ML_ROUND_MLROOM_H_
#define ML_ROUND_MLROOM_H_

#include <cocos2d.h>

#include "marco.h"
#include "reference/ml_reference.h"
#include "support/xjmath/XJMath.h"

namespace magicland {

class MLCamera;

class MLRoom:public MLReference {
public:
  MLRoom();
  virtual ~MLRoom();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLRoom);

    // setter and getter
public:
	void SetScene(cocos2d::CCScene* scene);
	cocos2d::CCScene* GetScene() const;

	void SetBackground(cocos2d::CCSprite* background);
	cocos2d::CCSprite* GetBackground() const;

	void SetGameLayer(cocos2d::CCLayer* layer);
	cocos2d::CCLayer* GetGameLayer() const;

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
	cocos2d::CCScene*	m_Scene;        // The scene of this room
	cocos2d::CCSprite*	m_Background;   // The background sprite
	cocos2d::CCLayer*	m_GameLayer;	// The game layer which hold all the game's sprite
	MLCamera*	m_Camera;       // The camera to look at this room
	int			m_TileWidth;    // The tile's width
	int			m_TileHeight;   // The tile's height
	int			m_RoomHeight;   // The room's height
	int			m_RoomWidth;    // The room's width
	char*		m_RoomMap;      // The room's map
	
	struct TerrianBoundBox {
		VECTOR2 min;
		VECTOR2 max;
	};

	std::vector<TerrianBoundBox> m_Terrians; // The vector hold all the terrian's bound box
};

}; // namespace magicland

#endif // ML_ROUND_MLROOM_H_