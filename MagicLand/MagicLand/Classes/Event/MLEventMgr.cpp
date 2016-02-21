#include "MLEventMgr.h"
#include "../marco.h"
using namespace MagicLand;

MLEventMgr* MLEventMgr::s_Instance = NULL;

MLEventMgr::MLEventMgr()
{
	m_SenderTable.clear();
	m_RecieverTable.clear();
	m_SenderTable.resize(MLEventMgr::MLEVENT_TOTAL);
	m_RecieverTable.resize(MLEventMgr::MLEVENT_TOTAL);

	m_UnRegistSendEventList.clear();
	m_UnRegistRecieveEventList.clear();
}

MLEventMgr::~MLEventMgr()
{
	// Clear the sender table
	for(unsigned int i = 0; i < m_SenderTable.size(); i++)
	{
		MLSenderList& temp = m_SenderTable[i];
		std::list<MLEntity*>::iterator it = temp.senderList.begin();
		for(; it != temp.senderList.end(); ++it)
		{
			ML_SAFE_DROP((*it));
		}

		temp.senderList.clear();
	}
	m_SenderTable.clear();

	// Clear the reciever table
	for(unsigned int i = 0; i < m_RecieverTable.size(); i++)
	{
		MLRecieverList& temp = m_RecieverTable[i];
		std::list<MLRecieverList::MLRecieverInfo>::iterator it = temp.recieverList.begin();
		for(; it != temp.recieverList.end(); ++it)
		{
			ML_SAFE_DROP(it->entity);
		}

		temp.recieverList.clear();
	}
	m_RecieverTable.clear();

	// Clear the unregist send event list for this frame
	for(unsigned int i = 0; i < m_UnRegistSendEventList.size(); i++)
	{
		MLRegistInfo registInfo = m_UnRegistSendEventList[i];
		MLEntity* sender = registInfo.entity;
		ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");
		if(sender != NULL)
		{
			ML_SAFE_DROP(sender);
		}
	}
	m_UnRegistSendEventList.clear();

	// Clear the unregist recieve event list for this frame
	for(unsigned int i = 0; i < m_UnRegistRecieveEventList.size(); i++)
	{
		MLRegistInfo registInfo = m_UnRegistRecieveEventList[i];
		MLEntity* reciever = registInfo.entity;
		ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exist");
		if(reciever != NULL)
		{
			ML_SAFE_DROP(reciever);
		}
	}
	m_UnRegistRecieveEventList.clear();
}

MLEventMgr* MLEventMgr::SharedInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new MLEventMgr();
	}

	return s_Instance;
}

void MLEventMgr::Destroy()
{
	ML_SAFE_DELETE(s_Instance);
}

void MLEventMgr::RegistRecieveEvent(unsigned int eventType, MLEntity* reciever, MLEventHandle handle)
{
	ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
	ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exsit");

	MLRecieverList::MLRecieverInfo info;
	info.entity = reciever;
	info.handle = handle;
	ML_SAFE_GRAB(reciever);

	m_RecieverTable[eventType].recieverList.push_back(info);
}

void MLEventMgr::UnRegistRecieveEvent(unsigned int eventType, MLEntity* reciever)
{
	ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
	ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exsit");
	
	MLRegistInfo info;
	info.entity = reciever;
	ML_SAFE_GRAB(reciever);
	info.eventType = eventType;
	m_UnRegistRecieveEventList.push_back(info);
}

void MLEventMgr::RegistSendEvent(unsigned int eventType, MLEntity* sender)
{
	ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
	ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exsit");
	
	m_SenderTable[eventType].senderList.push_back(sender);
}

void MLEventMgr::UnRegistSendEvent(unsigned int eventType, MLEntity* sender)
{
	ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
	ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");

	MLRegistInfo info;
	info.entity = sender;
	ML_SAFE_GRAB(sender);
	info.eventType = eventType;
	m_UnRegistSendEventList.push_back(info);
}

void MLEventMgr::Update(float delta)
{
	// Handle the event
	HandleEvents();

	// UnRegist the invalid event
	UnRegistEvents();
}

void MLEventMgr::Reset()
{
	// Clear the sender table
	for(unsigned int i = 0; i < m_SenderTable.size(); i++)
	{
		MLSenderList& temp = m_SenderTable[i];
		std::list<MLEntity*>::iterator it = temp.senderList.begin();
		for(; it != temp.senderList.end(); ++it)
		{
			ML_SAFE_DROP((*it));
		}

		temp.senderList.clear();
	}
	m_SenderTable.clear();

	// Clear the reciever table
	for(unsigned int i = 0; i < m_RecieverTable.size(); i++)
	{
		MLRecieverList& temp = m_RecieverTable[i];
		std::list<MLRecieverList::MLRecieverInfo>::iterator it = temp.recieverList.begin();
		for(; it != temp.recieverList.end(); ++it)
		{
			ML_SAFE_DROP(it->entity);
		}

		temp.recieverList.clear();
	}
	m_RecieverTable.clear();

	// Clear the unregist send event list for this frame
	for(unsigned int i = 0; i < m_UnRegistSendEventList.size(); i++)
	{
		MLRegistInfo registInfo = m_UnRegistSendEventList[i];
		MLEntity* sender = registInfo.entity;
		ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");
		if(sender != NULL)
		{
			ML_SAFE_DROP(sender);
		}
	}
	m_UnRegistSendEventList.clear();

	// Clear the unregist recieve event list for this frame
	for(unsigned int i = 0; i < m_UnRegistRecieveEventList.size(); i++)
	{
		MLRegistInfo registInfo = m_UnRegistRecieveEventList[i];
		MLEntity* reciever = registInfo.entity;
		ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exist");
		if(reciever != NULL)
		{
			ML_SAFE_DROP(reciever);
		}
	}
	m_UnRegistRecieveEventList.clear();
}

void MLEventMgr::HandleEvents()
{
	for(unsigned int eventType = 0; eventType < MLEVENT_TOTAL; eventType++)
	{
		std::list<MLRecieverList::MLRecieverInfo>::iterator itReciever = m_RecieverTable[eventType].recieverList.begin();
		for(; itReciever != m_RecieverTable[eventType].recieverList.end(); ++itReciever)
		{
			MLRecieverList::MLRecieverInfo recieverInfo = *itReciever;
			
			// Handle all events for this reciever
			std::list<MagicLand::MLEntity*>::iterator itSender = m_SenderTable[eventType].senderList.begin();
			for(; itSender != m_SenderTable[eventType].senderList.begin(); ++itSender)
			{
				MLEntity* sender = *itSender;
				ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");
				if(sender != NULL)
				{
					ML_SAFE_ASSERT(recieverInfo.entity != NULL, "Please make sure the reciever exist");
					if(recieverInfo.entity != NULL)
					{
						// Handle the event
						recieverInfo.handle(sender, recieverInfo.entity);
					}
				}
			}
		}
	}
}

void MLEventMgr::UnRegistEvents()
{
	// UnRegist sender events
	UnRegistSendEvents();

	// UnRegist reciever events
	UnRegistRecieveEvents();
}

void MLEventMgr::UnRegistSendEvents()
{
	// Un regist the send event
	std::vector<MLRegistInfo>::iterator it = m_UnRegistSendEventList.begin();
	for(; it != m_UnRegistSendEventList.end(); ++it)
	{
		MLRegistInfo registInfo = *it;
		MLEntity* sender = registInfo.entity;
		unsigned int eventType = registInfo.eventType;

		ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
		if(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL)
		{
			ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");
			if(sender != NULL)
			{
				m_SenderTable[eventType].senderList.remove(sender);
				ML_SAFE_DROP(sender);
			}
		}
	}

	// Clear the unregist send event list for this frame
	it = m_UnRegistSendEventList.begin();
	for(; it != m_UnRegistSendEventList.end(); ++it)
	{
		MLRegistInfo registInfo = *it;
		MLEntity* sender = registInfo.entity;
		ML_SAFE_ASSERT(sender != NULL, "Please make sure the sender exist");
		if(sender != NULL)
		{
			ML_SAFE_DROP(sender);
		}
	}
	m_UnRegistSendEventList.clear();
}

void MLEventMgr::UnRegistRecieveEvents()
{
	// Un regist the recieve event
	std::vector<MLRegistInfo>::iterator it = m_UnRegistRecieveEventList.begin();
	for(; it != m_UnRegistRecieveEventList.end(); ++it)
	{
		MLRegistInfo registInfo = *it;
		MLEntity* reciever = registInfo.entity;
		unsigned int eventType = registInfo.eventType;

		ML_SAFE_ASSERT(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL, "Please make sure the eventType is right");
		if(MLEVENT_START < eventType && eventType < MLEVENT_TOTAL)
		{
			ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exsit");
			if(reciever != NULL)
			{
				std::list<MLRecieverList::MLRecieverInfo>::iterator it = m_RecieverTable[eventType].recieverList.begin();
				for(; it != m_RecieverTable[eventType].recieverList.end(); ++it)
				{
					if(it->entity == reciever)
					{
						ML_SAFE_DROP(it->entity);
						m_RecieverTable[eventType].recieverList.erase(it);
						break;
					}
				}
			}
		}
	}

	// Clear the unregist recieve event list for this frame
	it = m_UnRegistRecieveEventList.begin();
	for(; it != m_UnRegistRecieveEventList.end(); ++it)
	{
		MLRegistInfo registInfo = *it;
		MLEntity* reciever = registInfo.entity;
		ML_SAFE_ASSERT(reciever != NULL, "Please make sure the sender exist");
		if(reciever != NULL)
		{
			ML_SAFE_DROP(reciever);
		}
	}
	m_UnRegistRecieveEventList.clear();
}