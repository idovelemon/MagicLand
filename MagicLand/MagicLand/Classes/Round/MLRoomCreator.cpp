#include"MLRoomCreator.h"
#include"../EntityComponent/MLEntityCreator.h"
#include"../EntityComponent/MLEntityMgr.h"
#include"../marco.h"
#include"../Camera/PlayerCamera/MLPlayerCamera.h"
#include<fstream>
using namespace std;
using namespace MagicLand;

MLRoomCreator::MLRoomCreator(const char* roomDataFileName)
	:m_RoomDataFileName(NULL)
{
	ML_SAFE_ASSERT(roomDataFileName != NULL, "Please pass a room data file");

	int length = strlen(roomDataFileName);
	m_RoomDataFileName = new char[length + 1];
	ML_SAFE_ASSERT(m_RoomDataFileName != NULL, "failed to allocate memory");

	memcpy(m_RoomDataFileName, roomDataFileName, length);
	m_RoomDataFileName[length] = '\0';
}

MLRoomCreator::~MLRoomCreator()
{
	ML_SAFE_DELETE_ARRAY(m_RoomDataFileName);
}

MLRoom* MLRoomCreator::CreateRoom()
{
	MLRoom* room = new MLRoom;
	ML_SAFE_ASSERT(room != NULL, "failed allocated memory for the room");

	// Config the room according th room data
	ReadRoomFileData(room);

	// Create game layer
	CreateLayer(room);

	// Create the room's entity
	CreateEntities(room);

	// Create the camera
	CreateCamera(room);

	return room;
}

void MLRoomCreator::ReadRoomFileData(MLRoom* room)
{
	ML_SAFE_ASSERT(room != NULL, "please make sure the room is not null");

	ifstream input;
	input.open(m_RoomDataFileName);
	ML_SAFE_ASSERT(!input.fail(), "can not find the specific file");

	// Read the size of the map
	int mapWidth = 0, mapHeight = 0;
	input >> mapWidth >> mapHeight;
	ML_SAFE_ASSERT(!input.eof(), "please input the right format file");
	room->SetRoomWidth(mapWidth);
	room->SetRoomHeight(mapHeight);

	// Read the tile's size
	int tileWidth = 0, tileHeight = 0;
	input >> tileWidth >> tileHeight;
	ML_SAFE_ASSERT(!input.eof(), "please input the right format file");
	room->SetTileWidth(tileWidth);
	room->SetTileHeight(tileHeight);

	// Read the map
	char* map = new char[mapWidth * mapHeight];
	ML_SAFE_ASSERT(map != NULL, "failed allocated memory for the room");
	memset(map, 0, sizeof(char) * mapWidth * mapHeight);

	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			input >> map[y * mapWidth + x];
			map[y * mapWidth + x] -= '0';
		}
	}
	room->CopyRoomMap(map);

	// Read the terrian
	int numTerrians = 0;
	input >> numTerrians;
	ML_SAFE_ASSERT(!input.eof(), "please input the right format file");

	for(int i = 0; i < numTerrians; i++)
	{
		VECTOR2 min, max;
		input >> min.x >> min.y >> max.x >> max.y;
		room->AddTerrianBoundBox(min, max);
	}

	input.close();
}

void MLRoomCreator::CreateLayer(MLRoom* room)
{
	// Save the running scene
	room->SetScene(CCDirector::sharedDirector()->getRunningScene());

	// Create the game layer
	CCLayer* gameLayer = CCLayer::create();
	gameLayer->setAnchorPoint(ccp(0.0f, 0.0f));
	gameLayer->setPosition(ccp(0.0f, 0.0f));
	room->GetScene()->addChild(gameLayer);
	room->SetGameLayer(gameLayer);
	gameLayer = NULL;
}

void MLRoomCreator::CreateEntities(MLRoom* room)
{
	ML_SAFE_ASSERT(room != NULL, "please make sure the room is not null");

	// Create the entity according the room's map
	char* map = room->GetRoomMap();
	ML_SAFE_ASSERT(map != NULL, "Please make sure the room map already loaded");

	int mapWidth = room->GetRoomWidth();
	int mapHeight = room->GetRoomHeight();
	int tileWidth = room->GetTileWidth();
	int tileHeight = room->GetTileHeight();

	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			MLEntitySubType type = (MLEntitySubType)map[y * mapWidth + x];
			if(type != ML_ETYSUBTYPE_EMPTY)
			{
				MLEntity* entity = MLEntityCreator::CreateEntity(type, x, y, room);
				ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");
				MLEntityMgr::SharedInstance()->AddEntity(entity);
			}
		}
	}

	// Create terrian entity according the terrian vector
	for(int i = 0; i < room->GetTerrianNum(); i++)
	{
		VECTOR2 min, max;
		room->GetTerrianAt(i, min, max);

		MLEntity* entity = MLEntityCreator::CreateTerrianEntity(min, max, room);
		ML_SAFE_ASSERT(entity != NULL, "Failed to create terrian entity");

		MLEntityMgr::SharedInstance()->AddEntity(entity);
	}
}

void MLRoomCreator::CreateCamera(MLRoom* room)
{
	ML_SAFE_ASSERT(room != NULL, "please make sure the room is not null");
	ML_SAFE_ASSERT(room->GetGameLayer() != NULL, "please make sure the gamer layer is not null");

	MLCamera* playerCamera = new MLPlayerCamera(room->GetGameLayer());
	ML_SAFE_ASSERT(playerCamera != NULL, "please make sure the playerCamera is not null");

	room->SetCamera(playerCamera);
	ML_SAFE_DROP(playerCamera);
}