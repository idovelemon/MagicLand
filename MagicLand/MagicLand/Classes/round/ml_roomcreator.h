//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/01
// Version:1.0
// Brief: This file will define the room creator. It will create the room
// from the round's data.
//------------------------------------------------------------------------
#ifndef ML_ROUND_MLROOMCREATOR_H_
#define ML_ROUND_MLROOMCREATOR_H_

#include "marco.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLRoom;

class MLRoomCreator:public MLReference {
public:
	explicit MLRoomCreator(const char* roomDataFile);
	virtual ~MLRoomCreator();

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

	char* m_RoomDataFileName;   // The room's file's name

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLRoomCreator);
};

}; // namespace magicland

#endif // ML_ROUND_MLROOMCREATOR_H_