#include "round/ml_round.h"

#include "marco.h"
#include "round/ml_room.h"
#include "round/ml_roomcreator.h"

using namespace magicland;

MLRound* MLRound::s_Instance = NULL;

MLRound::MLRound()
	:m_CurRoom(NULL) {
	MLRoomCreator* creator = new MLRoomCreator("test.rmd");
	ML_SAFE_ASSERT(creator != NULL, "Failed to allocate memory for the creator");
	m_CurRoom = creator->CreateRoom();
	ML_SAFE_DROP(creator);
}

MLRound::~MLRound() {
	ML_SAFE_DROP(m_CurRoom);
}

MLRound* MLRound::SharedInstance() {
	if (s_Instance == NULL) {
		s_Instance = new MLRound;
		ML_SAFE_ASSERT(s_Instance != NULL, "Failed create round");
	}

	return s_Instance;
}

void MLRound::Destroy() {
	ML_SAFE_DELETE(s_Instance);
}

void MLRound::Update(float delta) {
	ML_SAFE_ASSERT(m_CurRoom != NULL, "Please create the room first");
	m_CurRoom->Update(delta);
}

MLRoom* MLRound::GetCurRoom() const {
	return m_CurRoom;
}