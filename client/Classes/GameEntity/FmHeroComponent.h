/********************************************************************
created:	2013-01-07
author:		Fish (�ڹ�ƽ)
summary:	�����Ӷ����ģ�����,�ṩһЩͨ�ýӿ�
*********************************************************************/
#pragma once

#include "FmComponent.h"

NS_FM_BEGIN

class Hero;

class HeroComponent : public Component
{
public:
	HeroComponent( Entity* entity ) : Component( entity ) {}

	// ��ȡ�����Ӷ���
	Hero* GetHero();
};

NS_FM_END