/********************************************************************
created:	2013-01-22
author:		Fish (�ڹ�ƽ)
summary:	��Ⱦ��ص�ö��
*********************************************************************/
#pragma once

NS_FM_BEGIN


enum EEntityRenderTag
{
	EEntityRenderTag_Begin = 100,	// 100���¶��ǻ�װʹ��

	EEntityRenderTag_EntityName,	// ����
	//EEntityRenderTag_GuildName,		// ��������
	//EEntityRenderTag_FighterName,	// ͬ����
	EEntityRenderTag_HPBg,			// Ѫ������
	EEntityRenderTag_AngerBg,		// ŭ��������
	EEntityRenderTag_HP,			// Ѫ��
	EEntityRenderTag_Anger,			// ŭ����
	EEntityRenderTag_AngerFull,
	EEntityRenderTag_Lvl,		// �ȼ�����
	//EEntityRenderTag_Shout,			// ����
	EEntityRenderTag_ChengHao,		// �ƺ�

	//-------------------------------
	//EEntityRenderTag_FightUI,	

	EEntityRenderTag_SkillEffect	= 130,	// �˺�ֵ
	//EEntityRenderTag_BuffText	= 160,	// ����buff��ʾ����
	//-------------------------------

	EEntityRenderTag_EffectStart = 200,
	EEntityRenderTag_EffectEnd = 220,
};

//���ڼ���y������ڵ���ϵ
enum
{
	MAX_MAP_HEIGHT = 10000,
};
enum EZorderProperty
{
	EZorderProperty_BackBg ,
};

// ����
enum EDirection
{
	EDirection_Left = 0,	// ��
	EDirection_Right		// ��
};

//��ɫ�ο���߶�����
enum ERenderYOffsetType 
{
	ERenderYOffset_Foot,		// �ŵ�
	ERenderYOffset_HalfBody,	// ����
	ERenderYOffset_Head,		// ͷ��
};

//��ɫ�㼶
enum ERenderLayerType
{
	ERenderLayerType_Model,		// ģ��
	ERenderLayerType_Buff,
	ERenderLayerType_Effect,	// ��Ч
	ERenderLayerType_UI,		// UI(Ѫ��,����)

	ERenderLayerType_Max,
};

NS_FM_END