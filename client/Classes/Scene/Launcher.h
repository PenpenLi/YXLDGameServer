/********************************************************************
created:	2013-3-21
author:		SXH
summary:	launcher Scene
*********************************************************************/
#pragma once
#include "FmConfig.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "NetWork/RouterServer.pb.h"

NS_FM_BEGIN


USING_NS_CC;
USING_NS_CC_EXT;

using namespace gui;


class FileMgr;

enum E_LauncherStep
{
	E_LauncherStep_None,
	E_LauncherSteo_GetVersion,
	E_LauncherSteo_MediaVerCheck,	//�����汾���
	E_LauncherStep_Init,			//��ʼ��״̬
	E_LauncherStep_LoadConfig,		//��������
	E_LauncherStep_VerCheck,		//�汾���
	E_LauncherStep_CheckUrlFile,	//������Ҫ���ص��ļ�
	E_LauncherStep_LoadUrlFile,		//������Դ
	E_LauncherStep_LocalVerify,		//����Ч��
	E_LauncherStep_ResLoadFinished,	//��Դ�������
	E_LauncherStep_ResInit,			//��Դ��ʼ��
	E_LauncherStep_ResInit2,		//��Դ��ʼ��2
	E_LauncherStep_ResInitEnd,		//��Դ��ʼ������
	E_LauncherStep_SwitchGame,		//�л�����Ϸ����
	E_LauncherStep_Error,			//���ش���
	E_LauncherStep_MsgBox,			//�Ի���״̬
};

enum E_LauncherTag
{
	E_LauncherTag_Tips,
	E_LauncherTag_LoadTip,
	E_LauncherTag_LoadProgress,
	E_LauncherTag_MsgBox,
	E_LauncherTag_LoadBar,

};

const std::string s_VersionNumFileName = "version.config";
const std::string s_ResConfigFileName = "res.config";

class FmAudioEngineDelegate:public AudioEngineDelegate
{
public:
	SINGLETON_MODE( FmAudioEngineDelegate );
public:
	virtual void playEffect(const char* pszFilePath, bool bLoop);
	virtual void playBackgroundMusic(const char* pszFilePath, bool bLoop);
};
class Launcher:public CCLayer
{
public:
	static Launcher* GetInstance();
	static Launcher* create();
public:
	Launcher();
	virtual ~Launcher();
	virtual bool init();

	void SwitchStep(E_LauncherStep step);
	void MainLoop( uint delta );

	void UpdateTips(const char* remind);

	void UpdateLoadTips(const char* filename);
	void UpdateLoadProgress(int total,int cur);
	
	void UpdateLoadBar(const char* tips,int val);

	void ShowMessageBox( const char * titleStr,const char* msgStr,const char* leftStr,const char* rightStr, int tag );
	void HandleMessageBox( CCObject *pSender, TouchEventType type );
	void StartLoadRes();

	void OnVersionResponse(const char * resp);

	void UpdateLoadDummyProgressTips(float delta);
	void InitLoadProgressVal(int total,int destVal);
	void SetDestProgressValue(int val){m_DestProgressValue = val;};

	static void RouterVersion( int iCmd, ServerEngine::SCMessage& pkg );

private:
	bool ResInitLoad1();
	bool ResInitLoad2();
	bool ResInitLoad3();
	void WaitRS(float time);
	void Connect();
	void ReConnect(float time);
private:
	FileMgr*		m_AppResMgr;//apk �� boundle�������Դ����
	FileMgr*		m_LocalMgr; //�����ļ���Դ����
	FileMgr*		m_ServerMgr;//URL�������ļ���Դ����
	bool			m_Finished;
	bool			m_HasGetVersion; //�Ƿ��ȡ���汾��
	float			m_uiScale;
	int			m_DestProgressValue;
	int			m_TotalProgressValue;
	int			m_CurProgressValue;

	E_LauncherStep m_LauncherStep;
public:
	int				m_RequestFailCounter; //����ʧ�ܴ���
	string			m_url;
	string			m_version;
	string			m_UpdateVerUrl;
};


NS_FM_END
