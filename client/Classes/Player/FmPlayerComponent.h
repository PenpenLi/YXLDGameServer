/********************************************************************
created:	2013-01-07
author:		Fish (�ڹ�ƽ)
summary:	��ҵ�ģ�����,�ṩһЩͨ�ýӿ�
*********************************************************************/
#pragma once
#include "FmEntity.h"

//#include "GameEntity/FmSceneEntityComponent.h"

NS_FM_BEGIN

class Player;

class PlayerComponent : public Component
{
public:
	PlayerComponent( Entity* entity ) : Component( entity ) {}

	// ��ȡ��Ҷ���
	Player* GetPlayer();
};

NS_FM_END