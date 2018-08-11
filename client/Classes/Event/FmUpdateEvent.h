/********************************************************************
created:	2012-12-06
author:		Fish (�ڹ�ƽ)
summary:	�����¼�
*********************************************************************/
#pragma once

#include "FmEvent.h"

NS_FM_BEGIN

	// �����¼�
enum EUpdateEvent
{
	EUpdateEvent_Begin = 0x0200,

	EUpdateEvent_Update,			// ����

	EUpdateEvent_End	 = 0x02FF
};

class EventUpdate : public Event
{
public:
	uint	m_Delta;	// ��һ֡�ļ��

	EventUpdate( uint64 entityId, uint delta )
		: Event( EUpdateEvent_Update, entityId ), m_Delta( delta )
	{
	}
};

NS_FM_END