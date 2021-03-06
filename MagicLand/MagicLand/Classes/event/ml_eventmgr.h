//------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 02 / 02
// Version: 1.0
// Brief: This file will define the event manager. It will deal with all the event in this game
//------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLEVENTMGR_H_
#define ML_ENTITYCOMPONENT_MLEVENTMGR_H_

#include <list>
#include <vector>

#include "marco.h"

namespace magicland {

class MLEntity;

typedef void (*MLEventHandle)(magicland::MLEntity* sender, magicland::MLEntity* reciever);

class MLEventMgr {
public:
	enum {
		MLEVENT_START = -1,

		MLEVENT_TOTAL,
	};

	static MLEventMgr* SharedInstance();
	static void Destroy();

	virtual void RegistRecieveEvent(unsigned int eventType, magicland::MLEntity* reciever, MLEventHandle eventHandle);
	virtual void UnRegistRecieveEvent(unsigned int eventType, magicland::MLEntity* reciever);
	virtual void RegistSendEvent(unsigned int eventType, magicland::MLEntity* sender);
	virtual void UnRegistSendEvent(unsigned int eventType, magicland::MLEntity* sender);
	virtual void Update(float delta);
	virtual void Reset();

protected:
  struct MLSenderList {
		std::list<magicland::MLEntity*> senderList;
	};

	struct MLRecieverList {
		struct MLRecieverInfo {
			magicland::MLEntity* entity;
			MLEventHandle handle;
		};
		std::list<MLRecieverInfo> recieverList;
	};

	struct MLRegistInfo {
		unsigned int eventType;
		magicland::MLEntity* entity;
	};

  MLEventMgr();
	virtual ~MLEventMgr();

	void HandleEvents();
	void UnRegistEvents();
	void UnRegistSendEvents();
	void UnRegistRecieveEvents();

	std::vector<MLSenderList>	m_SenderTable;
	std::vector<MLRecieverList> m_RecieverTable;
	std::vector<MLRegistInfo>	m_UnRegistSendEventList;
	std::vector<MLRegistInfo>	m_UnRegistRecieveEventList;

	static MLEventMgr* s_Instance;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLEventMgr);
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLEVENTMGR_H_