/********************************************************************
created:	2012-05-20
author:		Fish (�ڹ�ƽ)
summary:	��Ϸ����
*********************************************************************/
#pragma once

#include "FmSafeTraverseSet.h"
#include "FmGeometry.h"
#include "cocoa/CCGeometry.h"
#include "FmMapLayer.h"
#include "GameEntity/FmHero.h"


NS_FM_BEGIN

class Scene
{
protected:
	uint					m_SceneId;			// ����id,ע��:���Ƕ���id
	SafeTraverseSet<uint>	m_SceneEntitys;		// �����ڵĶ���
	MapLayer*				m_mapLayer;
	CCLayer*				m_objLayer;
	CCLayer*				m_effectLayer;
	vector<CCPoint>			m_heroPosList;
	bool					m_pause;
public:
	static Scene* Create(uint sceneId);
	Scene();
	virtual ~Scene();
	
	void init(uint sceneId);

	void LoadTileMap();
	
	// ��������id
	uint GetSceneId() { return m_SceneId; }

	// �����ڵ��Ӷ���id�б�
	set<uint>& GetEntityIds();
	// �����ڵ��Ӷ���id�б�(���㵼����tolua++)
	void GetObjectList( vector<uint>& objectIds );

	// ���һ���Ӷ���
	void AddEntity( Hero* sceneEntity );
	// �Ƴ�һ���Ӷ���
	void RemoveEntity( uint entityId );

	//�ͷ����ж���
	void ReleaseAllEntity();

	// ����
	virtual void Update( uint delta );
	void AddEntityRender( EntityRender* entityRender);

	CCLayer* GetObjectLayer(){return m_objLayer;}
	CCLayer* GetEffectLayer(){return m_effectLayer;}
	vector<CCPoint>& GetHeroPosList(){return m_heroPosList;}
	void Pause();
	bool IsPause(){return m_pause;}
	void Resume(int iSkillID);
	void GetLeftHeroList(vector<Hero*>& heroList);
	Hero* GetLeftGodAnimal();
	void ChangeMap(int index);
};

NS_FM_END