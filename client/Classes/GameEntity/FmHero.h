/********************************************************************
created:	2012-06-02
author:		pelog
summary:	�����ڵĶ���
*********************************************************************/
#pragma once

#include "FmEntity.h"
#include "FmGeometry.h"
#include "cocos2d.h"
#include "Numeric/HeroBornData.h"
#include "InnatesKill/FmInnatesKill.h"
#include "InnatesKill/FmHeroFavorite.h"

USING_NS_CC;

NS_FM_BEGIN

class Scene;
class EntityRender;
class FightSoulBag;
class EquipBag;

class Hero : public Entity
{
protected:
	Hero( uint8 entityType, uint entityId, const string& name );

	Scene*	m_scene;		// ���ڳ�������id
	CCPoint m_Position;
	EntityRender* m_render;
	stHeroBornData* m_data;

public:
	virtual ~Hero();

	// �����ӿ�
	static Entity* Create( uint entityId, const string& entityName, EntityCreateOpt* createOpt );
	static void InitInterface();

	void SetData(stHeroBornData* data){m_data = data;}
	// ���½ӿ�
	virtual void Update( uint delta );

	// ��ǰ���ڵĳ�������id
	Scene* GetScene() { return m_scene; }

	// ���볡��
	virtual void OnEntryScene( Scene* scene );

	// �뿪����
	virtual void OnLeaveScene( Scene* scene );

	// ��ȡ��Ⱦ���
	EntityRender* GetRender();

	// ����
	CCPoint& GetPosition()  { return m_Position; }
	void SetPosition( CCPoint& position ) { m_Position=position; }

	stHeroBornData* GetHeroData();

	void AddRender(EntityRender* render){m_render = render;}

	// ����
	FightSoulBag* GetFightSoulBags();
	EquipBag* GetEquipBags();

	//�츳����
	InnatesKill* GetHeroInnateskill();

	//ϲ��Ʒ
	HeroFavorite* GetHeroFavorite();
};

NS_FM_END