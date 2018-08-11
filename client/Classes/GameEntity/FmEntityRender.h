/********************************************************************
created:	2012-12-09
author:		Fish (�ڹ�ƽ)
summary:	�����Ӷ������Ⱦģ��
*********************************************************************/
#pragma once

#include "FmEvent.h"
#include "FmGeometry.h"
#include "Enum/FmEntityRenderEnum.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Enum/FmCommonEnum.h"
#include "Effect/FmEffect.h"
#include "Skill/FmSkillResultData.h"
#include "Util/FmStateTimer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
NS_FM_BEGIN;

class Hero;

typedef map<string,string> RenderMap;

class EntityRender;
class RenderModeLayer : public CCLayer
{
	friend class EntityRender;
public:
	static RenderModeLayer* create(EntityRender* host);

	RenderModeLayer();
	virtual ~RenderModeLayer();

	virtual void onEnter();

	EntityRender* m_Host;

	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
	void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);
};

class EntityRender : public CCNode
{
	friend class RenderModeLayer;
	static int GetAutoTagId();
protected:
	RenderModeLayer* m_Layer[ERenderLayerType_Max];

	bool m_bFadeouted;
	int				m_tagId;
	//bool			m_IsCCbAnim;

	EAnims			m_currentAnimation;
	EAnims			m_nextAnimation;
	EAnims			m_lastAnimation;
	int				m_lastFrame;

	CCArmature*		m_armature;
	CCSize			m_contentSize;

	SkillResultData* m_data;
	stSkillData* m_skill;
	stSkillEffectData* m_skillEffect;
	Hero* m_hero;
	StateTimer	m_MainState;

	Hero* m_pAttackerHero;
	bool m_bMarkActorSkillKilled;
	bool m_bUILayerInited;
public:
	EntityRender(Hero* hero);
	virtual ~EntityRender();

	CCLayer* GetLayer(uint type) ;

	// �Ա����ֲ��ڹ��������ϲ��ţ�hurt��ʱ����Ҫ����Attaker���ϵ�State
	void setAttacker(Hero* pAttackerHero){m_pAttackerHero = pAttackerHero;}
	Hero* GetHero(){return m_hero;}
	int GetTagId(){return m_tagId;}
	int GetZorder();
	// ������Ⱦ����  modeName��̬���غ�ĸ���ģ��
	void InitAnim();
	bool BackToPosition();

	void SetVisible(bool visible);

	// ���ö���
	void SetAnimation(EAnims ani);
	void SetAnimation(EAnims ani,int loop);

	// ��ȡ��ǰ����
	EAnims GetCurrentAnimation();

	void initUILayer();

	// ���÷�ת
	void SetFlipX( bool flip);
	bool IsFlipX();
	// ���ó���,�Զ���Flip
	void SetDirection( FmPoint targetPt );

	void markActorSkillKilled(){m_bMarkActorSkillKilled = true;}

	//��ȡ��ʾ��Դ·��
	string GetAnimPath();
	string GetAnimName();
	float GetAnimScale();


	float GetHeight();
	float GetHeight(int type); //��Ը߶�

	CCSize GetContentSize();

	//��Ч
	void AddEffect(EffectNode* enode);
	void AddEffectByName(const char* name);
	void AddEffect(EffectNode* enode,const CCPoint& posOffSet);
	void AddEffectByName(const char* name,const CCPoint& posOffSet);
	void RemoveEffect(const char* name);
	void AddEffectById( int effectId );
	void AddEffectById( int effectId, const CCPoint& posOffset);
	void RemoveEffectById(int effectId);
	void RemoveAllEffect();

	bool isMultiDamageSkill();

	//����Ч�� time�Ǻ���
	void FadeOut( int time );
	//����Ч�� time�Ǻ���
	void FadeIn( int time );

	void FadeEndCall();

	void SetPosition(CCPoint pos);

	CCArmature* GetArmature();

	
	bool GetFlipByFormationPos();
	int GetEffectTag();

	void PlayAttAnim(SkillResultData* data);
	CCPoint GetDestPosByHero(Hero* hero);
	CCPoint GetCurPos();
	void PlayNormalFarAtt(EAnims anim = EAnimsAtt);
	void PlayNormalNearAtt(EAnims anim = EAnimsAtt);
	void PlayHurtEffect(stSkillEffectData* skillEffect);
	void PlayZiBaoHurtEffect();
	void PlayEffect(const string& strEffectName);
	void PlayUIEffect(const string& strEffectName);
	void Update(uint detla);

	bool MoveAction(CCPoint targetPos,float time, EAnims anim);
	void MoveEndCall();
	void PlayButtletEffect();

	void ButtleEndCall(void* data);

	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
	void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);
	string GetEffectPathByName(string name);
	void AddBuff(int id);
	void RemoveBuff(int id);
	bool GetFlipByTargetFormationPos(Hero* hero);
	void Pause();
	void Resume(int iSkillID);
	void moveWithParabola(CCNode* node, CCPoint startPoint, CCPoint endPoint, float startAngle, float endAngle, float time);
	void CheckIsNeedStop();

	void RevertAnim();
};

NS_FM_END