/********************************************************************
created:	2012-11-17
author:		Fish (�ڹ�ƽ)
summary:	���id
*********************************************************************/
#pragma once
#include "FmConfig.h"

NS_FM_BEGIN

	// ���id
enum EComponentId
{
	EComponentId_DataSync = 1,		// ����ͬ��
	EComponentId_EntityRender,		// ʵ����Ⱦģ��
	EComponentId_FightSoulBags,		// ��걳��
	//EComponentId_Quest,				// ����ģ��
	EComponentId_Bags,				// ����ģ��
	EComponentId_EquipBags,				// װ��ģ��
	EComponentId_Materail,				// װ����Ƭģ��
	EComponentId_InnatesKill,           //�츳����
	EComponentId_HeroSoul,              //Ӣ�ۻ���
	EComponentId_HeroFavorite,          //Ӣ��ϲ��
};

NS_FM_END