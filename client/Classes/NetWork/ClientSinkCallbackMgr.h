/********************************************************************
created:	2014-3-3
author:		pelog
summary:	�ͻ��˵���Ϣ�ص�����
*********************************************************************/
#pragma once
#include "RouterServer.pb.h"
#include "FmConfig.h"
#include "GameServer.pb.h"

NS_FM_BEGIN
using namespace ServerEngine;
using namespace GSProto;

typedef void (*RSCallback)( int iCmd, ServerEngine::SCMessage& pkg);
typedef void (*Callback)( int iCmd, GSProto::SCMessage& pkg);
// ��Ϣ�ص�����
class ClientSinkCallbackMgr
{
public:
	typedef UNORDERED_MAP< int, RSCallback > PacketRSCallbackMap; // ��Ϣ�ź���Ϣ�ص�������ӳ���
	typedef UNORDERED_MAP< int, Callback > PacketCallbackMap; // ��Ϣ�ź���Ϣ�ص�������ӳ���
protected:
	PacketRSCallbackMap		m_PacketRSCallbacks;
	PacketCallbackMap		m_PacketCallbacks;
public:
	ClientSinkCallbackMgr() {}
	virtual ~ClientSinkCallbackMgr() {}

	SINGLETON_MODE( ClientSinkCallbackMgr );

	// ע����Ϣ�ص�
	bool RegisterRS (int commandId, RSCallback packetCallback )
	{
		if( GetRSCallback( commandId ) != NULL )
		{
			Assert( false );
			return false;
		}
		m_PacketRSCallbacks[commandId] = packetCallback;
		return true;
	}

	// get
	RSCallback GetRSCallback( int commandId )
	{
		PacketRSCallbackMap::iterator it = m_PacketRSCallbacks.find( commandId );
		if( it != m_PacketRSCallbacks.end() )
		{
			return (it->second);
		}
		return NULL;
	}

	// ע����Ϣ�ص�
	bool Register (int commandId, Callback packetCallback )
	{
		if( GetCallback( commandId ) != NULL )
		{
			Assert( false );
			return false;
		}
		m_PacketCallbacks[commandId] = packetCallback;
		return true;
	}

	// get
	Callback GetCallback( int commandId )
	{
		PacketCallbackMap::iterator it = m_PacketCallbacks.find( commandId );
		if( it != m_PacketCallbacks.end() )
		{
			return (it->second);
		}
		return NULL;
	}

	// ��Ϣ�ص�����
	virtual bool ProcessRSPacket(int iCmd, ServerEngine::SCMessage& pkg )
	{
		RSCallback packetRSCallback = GetRSCallback( iCmd );
		if( packetRSCallback )
		{
			packetRSCallback( iCmd, pkg );
			return true;
		}
		
		return false;
	}

	// ��Ϣ�ص�����
	virtual bool ProcessPacket(int iCmd, GSProto::SCMessage& pkg )
	{
		Callback packetCallback = GetCallback( iCmd );
		if( packetCallback )
		{
			packetCallback( iCmd, pkg );
			return true;
		}
		return false;
	}
};

NS_FM_END