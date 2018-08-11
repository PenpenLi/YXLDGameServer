/********************************************************************
created:	2013-3-4
author:		pelog
summary:	��Ϸ��������
*********************************************************************/
#pragma once

#include "FmConfig.h"
#include "FmScene.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "NetWork/GameServer.pb.h"
#include "Enum/FmCommonEnum.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace gui;

NS_FM_BEGIN

class PerformenceCounter
{
public:

	PerformenceCounter(const char* strName);
	~PerformenceCounter();

private:
	std::string m_strName;
	uint m_dwBeginCounter;
};


class SceneMgr
{
protected:
	Scene*	m_Scene;	// ��ǰ����
	Scene*	m_PreScene; // ��һ������

	EGameState m_State;

	ESLoadStep	m_LoadStep;

	bool		m_bGotoMainmenu;

	bool		m_isFromMainmenu;

	bool		m_isServerDataFinish;

	uint		m_lastState;
	
	bool       m_bHeroCacheDirty;
	std::map<int, CCArmature*> m_cacheFormationHeroList;
	//std::set<string> m_cachedAnimationList; // ��ʱCache�Ķ���(��ֹ���볡��ʱ��ͬ���������SpriteFrame)

	//uint		m_curWeatherId; //��ǰ����
private:
	void SwitchToNextState();
	void updateHeroCache();
public:
	SceneMgr();
	virtual ~SceneMgr();

	SINGLETON_MODE( SceneMgr );

	//void SetWeather(int id);
	//int GetWeather(){return m_curWeatherId;};

	//���ó��������ɫ
	//void SetSceneBlendColor(ccColor3B color);

	// ��ǰ����
	Scene* GetCurScene() { return m_Scene; }

	void SwitchState( EGameState newState, EGameState nextState);
	void SwitchFightingScene(uint sceneId);

	void SwitchToMainMenu();

	void ShowMainMenuSceneUi();

	CCArmature* queryCacheArmature(int iHeroID);

	void freeUnusedMemory();

	int Update(uint delta);
	int UpdateLoading(uint delta);

	void AddEntity(Hero* entity);
	void RemoveEntity(uint id);

	void SwitchToMainUi(bool isFromMainmenu = false);
	void SwitchToTerritory();

	static void RoleFinish( int iCmd, GSProto::SCMessage& pkg );
	static void GetRole( int iCmd, GSProto::SCMessage& pkg );
	static void GetHeroList( int iCmd, GSProto::SCMessage& pkg );
	static void GetFormationList( int iCmd, GSProto::SCMessage& pkg );
	static void GetHeroFightSoulBag( int iCmd, GSProto::SCMessage& pkg );
	static void GetBagData( int iCmd, GSProto::SCMessage& pkg );
	static void UpdateBagData( int iCmd, GSProto::SCMessage& pkg );
	static void GetGodAnimalList(int iCmd, GSProto::SCMessage& pkg);

	static void GetFightSoulBag( int iCmd, GSProto::SCMessage& pkg );
	static void GetEquipBag( int iCmd, GSProto::SCMessage& pkg );
	static void GetHeroEquipBag( int iCmd, GSProto::SCMessage& pkg );

		void SetLoadStep(ESLoadStep step){m_LoadStep = step;}
	int GetGameState(){return m_State;}
	void UpdateLoadBar( const char* tips,int val );

	void SetIsServerDataFinish(bool isFin){m_isServerDataFinish = isFin;}

	int GetLastState(){return m_lastState;}
	void SwitchToMyTerritory();
	void AddEntityInToScene(const GSProto::FightObj& data, bool isFromSky = false);

	void CleanEntitys(bool isAttack);
	//����Ч��
	//void AddWeatherEffect();
	EGameState m_nextState;
};

static Scene* GetCurScene()
{
	return SceneMgr::GetInstance().GetCurScene();
}

NS_FM_END