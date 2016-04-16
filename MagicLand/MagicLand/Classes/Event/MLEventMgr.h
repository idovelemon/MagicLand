//------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 02 / 02
// Version: 1.0
// Brief: This file will define the event manager. It will deal with all the event in this game
//------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLEVENTMGR_H_
#define ML_ENTITYCOMPONENT_MLEVENTMGR_H_

#include <list>
#include <vector>

namespace MagicLand 
{
	class MLEventMgr;
	class MLEntity;
};

typedef void (*MLEventHandle)(MagicLand::MLEntity* sender, MagicLand::MLEntity* reciever);

class MagicLand::MLEventMgr
{
public:
	enum
	{
		MLEVENT_START = -1,

		MLEVENT_TOTAL,
	};
protected:
	MLEventMgr();
	virtual ~MLEventMgr();

public:
	static MLEventMgr* SharedInstance();
	static void Destroy();

public:
	virtual void RegistRecieveEvent(unsigned int eventType, MagicLand::MLEntity* reciever, MLEventHandle eventHandle);
	virtual void UnRegistRecieveEvent(unsigned int eventType, MagicLand::MLEntity* reciever);
	virtual void RegistSendEvent(unsigned int eventType, MagicLand::MLEntity* sender);
	virtual void UnRegistSendEvent(unsigned int eventType, MagicLand::MLEntity* sender);
	virtual void Update(float delta);
	virtual void Reset();

protected:
	void HandleEvents();
	void UnRegistEvents();
	void UnRegistSendEvents();
	void UnRegistRecieveEvents();

protected:
	struct MLSenderList
	{
		std::list<MagicLand::MLEntity*> senderList;
	};

	struct MLRecieverList
	{
		struct MLRecieverInfo
		{
			MagicLand::MLEntity* entity;
			MLEventHandle handle;
		};
		std::list<MLRecieverInfo> recieverList;
	};

	struct MLRegistInfo
	{
		unsigned int eventType;
		MagicLand::MLEntity* entity;
	};

	std::vector<MLSenderList>	m_SenderTable;
	std::vector<MLRecieverList> m_RecieverTable;
	std::vector<MLRegistInfo>	m_UnRegistSendEventList;
	std::vector<MLRegistInfo>	m_UnRegistRecieveEventList;

	static MLEventMgr* s_Instance;
};

#endif // ML_ENTITYCOMPONENT_MLEVENTMGR_H_