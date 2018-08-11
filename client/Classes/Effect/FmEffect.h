/********************************************************************
created:	2013-1-30
author:		SXH
summary:	��Ч
*********************************************************************/
#pragma once
#include "FmConfig.h"
#include "cocos2d.h"
#include "cocos-ext.h"
NS_FM_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;


#define MAX_EFFECT_FRAMES 10

//��Ч��������
class EffectData
{
public:
	EffectData();
	virtual ~EffectData();
public:
	int		m_Type;
	string	m_Path;
	string	m_Name;
	int		m_Zorder;
	int		m_X;
	int		m_Y;
	int		m_YOffsetType;	//Y��ɫ�߶Ȳο��� ERenderYOffsetType
	int		m_Loop;
	float	m_Scale;
	int		m_Life;
	int 	m_FrameDt; // ����
	int		m_Dir;		// ���� 0-Ĭ�� 1-������ 2-��ɫ���� 3-��ɫ�ķ�����
	int		m_Id;
	int		m_isAnim;
};

//��Ч�ڵ㣬����ά���Լ�����������
class EffectNode:public CCNode
{
public:
	static EffectNode* create(EffectData* data);
	static EffectNode* create();
	EffectNode(EffectData* data);
	EffectNode();
	~EffectNode();
	bool init();
	int GetZOrder();
	string& GetName();
	int GetId();
	int GetYOffsetType(); //��ɫ�߶Ȳο��� ERenderYOffsetType
	int GetDir();

	void SetFlipX(bool b);
	void SetFlipY(bool b);
	void callback();
	void updateTime(float dt);
	void Dead();
	void SetLife(float lf);
	uint GetLife(){return m_ConfigData->m_Life;}

	virtual void onExit();
	virtual void onEnter();
private:
	EffectData* m_ConfigData;
	int		m_Life;
	bool	m_isFlipX;
	bool	m_isFlipY;
};

class CloudEffect:public CCSprite
{
private:
	CCPoint m_Speed;
	CCSize	m_Size;
public:
	static CloudEffect* create(const char* path,const CCPoint& speed,const CCSize& size);
	void SetProp(const CCPoint& speed,const CCSize& size);
	void	UpdateTime(float dt);
};


//��Ч������
class EffectMgr
{
public:
	typedef UNORDERED_MAP<std::string,EffectData*> EffectDataMap;

protected:
	EffectDataMap	m_EffectData;

public:
	EffectMgr();
	virtual ~EffectMgr();

	SINGLETON_MODE( EffectMgr );

	bool Init();

	const EffectData* GetEffectDataByName(const char* name) const;

	EffectNode* GetEffectNode(const char* name);

	void AddEffect(CCNode* panl,EffectNode* enode,int tag);
	void AddEffect(CCNode* panl,const char* name,int tag);
	void StopEffect( CCNode* panl,EffectNode* enode );
	EffectData* GetEffectDataById(const int id) const;
	EffectNode* GetEffectNodeById( int effectId );

	void Shutdown();
	static void AddButtonPromotToNode( Widget* node, int zOrder, int tag ,bool isCircle = false,int time = 0);
};


class CCParticleBtnTip : public CCParticleSystemQuad
{
public:
	CCParticleBtnTip(){}
	virtual ~CCParticleBtnTip(){}
	bool init(){ return initWithTotalParticles(180); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);

	void setRight();
	void setUp();
	void setLeft();
	void setDown();

	void setProperty(float life,float speed);
	
	static CCParticleBtnTip * create(int num);
	static CCParticleBtnTip* createWithTotalParticles(unsigned int numberOfParticles);
	static void RunOnNode(CCNode* node,int zOrder,int tag, bool isRect=true);

	static CCParticleSystemQuad* CreateParticle(CCPoint pos,CCRect boundingBox, bool isRect=true );
};
NS_FM_END
