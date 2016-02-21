#include "MLRoom.h"
#include "../marco.h"
#include "../Event/MLEventMgr.h"
#include "../EntityComponent/MLEntityMgr.h"
#include "../Collision/MLCollisionMgr.h"

using namespace MagicLand;

MLRoom::MLRoom()
	:m_Scene(NULL)
	,m_Background(NULL)
	,m_GameLayer(NULL)
	,m_Camera(NULL)
	,m_TileWidth(0)
	,m_TileHeight(0)
	,m_RoomHeight(0)
	,m_RoomWidth(0)
	,m_RoomMap(NULL)
{
	m_Terrians.clear();
}

MLRoom::~MLRoom()
{
	Destroy();
}

void MLRoom::SetScene(CCScene* scene)
{
	ML_SAFE_ASSERT(scene != NULL, "Please pass a valid layer pointer");
	m_Scene = scene;
	m_Scene->retain();
}

CCScene* MLRoom::GetScene() const
{
	return m_Scene;
}

void MLRoom::SetBackground(CCSprite* background)
{
	ML_SAFE_ASSERT(background != NULL, "Please pass a valid background pointer");
	m_Background = background;
	m_Background->retain();
}

CCSprite* MLRoom::GetBackground() const
{
	return m_Background;
}

void MLRoom::SetGameLayer(CCLayer* layer)
{
	ML_SAFE_ASSERT(layer != NULL, "Please pass a valid game layer");
	m_GameLayer = layer;
	m_GameLayer->retain();
}

CCLayer* MLRoom::GetGameLayer() const
{
	return m_GameLayer;
}

void MLRoom::SetCamera(MLCamera* camera)
{
	ML_SAFE_ASSERT(camera != NULL, "Please pass a valid camera pointer");
	m_Camera = camera;
	ML_SAFE_GRAB(m_Camera);
}

MLCamera* MLRoom::GetCamera() const
{
	return m_Camera;
}

void MLRoom::SetRoomHeight(int height)
{
	m_RoomHeight = height;
}

int MLRoom::GetRoomHeight() const
{
	return m_RoomHeight;
}

void MLRoom::SetRoomWidth(int width)
{
	m_RoomWidth = width;
}

int MLRoom::GetRoomWidth() const
{
	return m_RoomWidth;
}

void MLRoom::SetTileWidth(int width)
{
	m_TileWidth = width;
}

int MLRoom::GetTileWidth() const
{
	return m_TileWidth;
}

void MLRoom::SetTileHeight(int height)
{
	m_TileHeight = height;
}

int MLRoom::GetTileHeight() const
{
	return m_TileHeight;
}

void MLRoom::CopyRoomMap(const char* map)
{
	ML_SAFE_ASSERT(map != NULL, "map can not be null pointer");
	ML_SAFE_ASSERT(m_RoomHeight > 0, "must set the room's size before copy room's map");
	ML_SAFE_ASSERT(m_RoomWidth > 0, "must set the room's size before copy room's map");

	ML_SAFE_DELETE_ARRAY(m_RoomMap);
	m_RoomMap = new char[m_RoomWidth * m_RoomHeight];
	ML_SAFE_ASSERT(m_RoomMap != NULL, "failed to allocate memory for room map");
	memcpy(m_RoomMap, map, sizeof(char) * m_RoomWidth * m_RoomHeight);
}

char* MLRoom::GetRoomMap() const
{
	return m_RoomMap;
}

char MLRoom::GetGridType(int x, int y)
{
	ML_SAFE_ASSERT(m_RoomMap != NULL, "must create room map first");
	ML_SAFE_ASSERT(m_RoomHeight > 0, "must create room map first");
	ML_SAFE_ASSERT(m_RoomWidth > 0, "must create room map first");
	ML_SAFE_ASSERT(0 <= x && x < m_RoomWidth, "please make sure the grid's coordinate is in the room");
	ML_SAFE_ASSERT(0 <= y && y < m_RoomHeight, "please make sure the grid's coordinate is in the room");

	return m_RoomMap[y * m_RoomWidth + x];
}

void MLRoom::TransformMapCoordToWorldCoord(int& x, int& y)
{
	int worldX = m_TileWidth/2 + x * m_TileWidth;
	int worldY = m_TileHeight/2 + (m_RoomHeight - y - 1) * m_TileHeight;
	x = worldX;
	y = worldY;
}

void MLRoom::AddTerrianBoundBox(VECTOR2 min, VECTOR2 max)
{
	TerrianBoundBox terrian;
	terrian.min = min;
	terrian.max = max;
	m_Terrians.push_back(terrian);
}

int MLRoom::GetTerrianNum() const
{
	return m_Terrians.size();
}

void MLRoom::GetTerrianAt(int index, VECTOR2& min, VECTOR2& max)
{
	ML_SAFE_ASSERT(index >= 0 && index < m_Terrians.size(), "Please make sure the index is valid");
	TerrianBoundBox terrian = m_Terrians[index];
	min = terrian.min;
	max = terrian.max;
}

bool MLRoom::Init()
{
	return true;
}

void MLRoom::Update(float delta)
{
	// Update the camera
	ML_SAFE_ASSERT(m_Camera != NULL, "Camera mustn't be null");
	m_Camera->Update(delta);

	// Update the event system
	MLEventMgr::SharedInstance()->Update(delta);

	// Update the entity system
	MLEntityMgr::SharedInstance()->Update(delta);

	// Update the collision system
	MLCollisionMgr::SharedInstance()->Update(delta);
}

void MLRoom::Destroy()
{
	if(m_Background != NULL)
	{
		m_Background->removeFromParent();
		m_Background->removeAllChildren();
		m_Background->release();
		m_Background = NULL;
	}

	if(m_Scene != NULL)
	{
		m_Scene->removeFromParent();
		m_Scene->removeAllChildren();
		m_Scene->release();
		m_Scene = NULL;
	}

	ML_SAFE_DELETE_ARRAY(m_RoomMap);
	ML_SAFE_DROP(m_Camera);
	m_Terrians.clear();

	MLEventMgr::SharedInstance()->Destroy();
	MLEntityMgr::SharedInstance()->Destroy();
	MLCollisionMgr::SharedInstance()->Destroy();
}