/********************************************************************
created:	2012-06-04
author:		Fish (�ڹ�ƽ)
summary:	�ű�ϵͳ
*********************************************************************/
#pragma once

#include "FmNet.h"
extern "C" {
#include "lua.h"
#include "tolua_fix.h"
}

NS_FM_BEGIN

class Player;

class ScriptSys
{
public:
	static uint s_RobetId;
protected:
	typedef UNORDERED_MAP< int, string >	ScriptFuncMap;
	ScriptFuncMap	m_ScriptFuncs;
	string			m_ScriptPath;			// �ű�Ŀ¼
public:
	ScriptSys();
	~ScriptSys();

	SINGLETON_MODE( ScriptSys );

	void Init();

	// ע��ű���Ϣ�ص�
	// �ص��ű�������ʽ: function OnPacket_XXXX( packetArg )
	void RegisterScriptFunc( int packetId, const char* scriptFunc );
	// ȡ��ע��ű���Ϣ�ص�
	void UnRegisterScriptFunc( int packetId );
	// ������Ϣ
	bool DispatchPacket( int iCmd, const string& pkg );

	// ��ȡlua������ӳ��id
	// ����1: lua����
	static int GetLuaFuncId( lua_State* L );

	// ����lua�ű��ļ�
	// ����1: lua�ļ���
	static int L_LoadFile( lua_State* L );
	static bool LoadFile( const char* luafile );

	static int ExecuteBuffer( lua_State* L, const char *buf, size_t size);

	// ����־
	static int L_LogFile( lua_State* L );
	static int L_IsDebug( lua_State* L );
	static int L_GetPlatform( lua_State* L );

	bool Execute( const char* funcName );

	bool ExecuteString( const char* str );

	// ִ��lua����,��һ������
	bool Execute_1( const char* funcName, void* value, const char* type );

	// ִ��lua����,��2������
	bool Execute_2( const char* funcName, void* value, const char* type, void* value2, const char* type2 );

	// ִ��lua����,��3������
	bool Execute_3( const char* funcName, void* value, const char* type, void* value2, const char* type2, void* value3, const char* type3 );

	bool Execute_4(const char* funcName, 
				   void* value, const char* type, 
				   void* value2, const char* type2, 
				   void* value3, const char* type3,
				   void* value4, const char* type4);

	static void ExecuteSchedulerScriptHandler( const char* script, Entity* entity, ScheduleFunctor* functor, uint delta );
	void ExecuteSchedulerScript( const char* script, Entity* entity, ScheduleFunctor* functor, uint delta );

	// 32λ������λ����
	static int L_ByteOp( lua_State* L );
	bool Execute_number( const char* funcName, int number );
	bool Execute_number( const char* funcName, int number1, int number2 );
	bool Execute_number( const char* funcName, int number1, int number2, int number3 );
};

NS_FM_END