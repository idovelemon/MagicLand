//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/01
// Version:1.0
// Brief: This file will define the room creator. It will create the room
// from the round's data.
//------------------------------------------------------------------------
#ifndef __MLROOMCREATOR__H_
#define __MLROOMCREATOR__H_

#include "../Reference/MLReference.h"
#include "MLRoom.h"

namespace MagicLand{ class MLRoomCreator;};

class MagicLand::MLRoomCreator:public MLReference
{
public:
	MLRoomCreator(const char* roomDataFile);
	virtual ~MLRoomCreator();

public:
	//------------------------------------------------------------------------
	// Description:Create a room according the room data
	// Ret:If the method success, return the created room; otherwise return null
	//------------------------------------------------------------------------
	virtual MLRoom* CreateRoom();

protected:
	//------------------------------------------------------------------------
	// Description:Read the room data from the file and set the room's attribute
	// Param:[out] room  The room that need to be config
	//------------------------------------------------------------------------
	void ReadRoomFileData(MLRoom* room);

	//------------------------------------------------------------------------
	// Desc: Create all the room's layer
	// Param:[out] room The room hold all the layer
	//------------------------------------------------------------------------
	void CreateLayer(MLRoom* room);

	//------------------------------------------------------------------------
	// Description:Create all the entities according the map data
	// Param:[out] room The room that hold all the entities
	//------------------------------------------------------------------------
	void CreateEntities(MLRoom* room);

	//------------------------------------------------------------------------
	// Desc: Create all the room's camera
	// Param:[out] room The room hold all the layer
	//------------------------------------------------------------------------
	void CreateCamera(MLRoom* room);

protected:
	char* m_RoomDataFileName;   // The room's file's name
};

#endif