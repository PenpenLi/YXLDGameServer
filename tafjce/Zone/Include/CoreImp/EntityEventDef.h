#ifndef __ENTITY_EVENT_DEF_H__
#define __ENTITY_EVENT_DEF_H__

enum
{
	EVENT_ENTITY_BEGIN,
	EVENT_ENTITY_PROPCHANGE,			// ���Ըı��¼�
	EVENT_ENTITY_PRE_RELEASE,  // Ԥ�����¼�
	EVENT_ENTITY_PREBEGIN_FIGHT,
	EVENT_ENTITY_BEGIN_FIGHT,		// ��ʼս��
	EVENT_ENTITY_END_FIGHT,			// ����ս��
	EVENT_ENTITY_BEGIN_ROUND,		// ��ʼ�غ�
	EVENT_ENTITY_END_ROUND,		// �����غϽ���
	EVENT_ENTITY_USESKILL,
	EVENT_ENTITY_USESKILL_FINISH,
	EVENT_ENTITY_PRE_ATTACK,			// ����ǰ
	EVENT_ENTITY_POST_ATTACK,
	EVENT_ENTITY_DEAD_WITHCONTEXT,
	EVENT_ENTITY_SENDACTOR_TOCLIENT, // ֪ͨ�ͻ��˽�ɫ��Ϣ�¼�
	EVENT_ENTITY_SENDACTOR_TOCLIENT_POST,
	EVENT_ENTITY_NEWHERO,   // ����Ӣ��
	EVENT_ENTITY_DELHERO,   // ɾ��Ӣ��
	EVENT_ENTITY_RELOGIN,   // �ص�¼

	EVENT_ENTITY_CREATED,   // ����ʵ�崴����ɺ����¼�
	EVENT_ENTITY_DODAMAGE,
	
	EVENT_ENTITY_BEDAMAGE,
	
	EVENT_ENTITY_PREDODAMAGE,
	EVENT_ENTITY_PREBEDAMAGE,
	EVENT_ENTITY_POSTDODAMAGE,
	EVENT_ENTITY_POSTBEDAMAGE,
	
	EVENT_ENTITY_LEVELUP,
	EVENT_ENTITY_POSTLEVELUP,
	
	EVENT_ENTITY_LEVELSTEPCHG, // �Ƚ�����,�仯
	EVENT_ENTITY_CALCGROW, // ֪ͨʵ�����¼���ɳ�

	EVENT_ENTITY_DOFIGHTPROPCHG, // ս�������Ա仯Result
	EVENT_ENTITY_POSTDOFIGHTPROPCHG,

	EVENT_ENTITY_BEFIGHTPROPCHG,
	EVENT_ENTITY_POSTBEFIGHTPROPCHG,

	EVENT_ENTITY_EFFECT_TOCHDOKILL,  // ��������ɱ
	EVENT_ENTITY_EFFECT_TOCHBEKILL,
	
	EVENT_ENTITY_EFFECTDOKILL,
	EVENT_ENTITY_EFFECTBEKILL,

	EVENT_ENTITY_CONTINUESKILL,  // �������ܿ�ʼ
	EVENT_ENTITY_RELIVE,  // ����

	EVENT_ENTITY_FIGHTVALUECHG, // Ӣ��ս���ı�

	EVENT_ENTITY_NEWBUFF,
	EVENT_ENTITY_RELEASEBUFF,

	EVENT_ENTITY_PASSSCENE,  // ͨ�عؿ�

	EVENT_ENTITY_FINISGUIDE,

	EVENT_ENTITY_OPENFUNCTION,

	EVENT_ENTITY_PERFECT_PASSSECTION, // ͨ���½�

	EVENT_ENTITY_FINISHCONDITION, //����ۻ���������

	EVENT_ENTITY_FINISHDUNGEONCONDITION,   //�����������
	
	EVENT_ENTITY_ACTIVEGODANIMAL_CHG, // ��ս���ޱ仯

	EVENT_ENTITY_PREEXE_EFFECT,						

	EVENT_ENTITY_TASKFINISH_LOOT,					//�Ӷ����

	EVENT_ENTITY_TASKFINISH_HEROLEVEL,				//Ӣ�۵ȼ�

	EVENT_ENTITY_TASKFINISH_SOUL,					//���ȼ�

	EVENT_ENTITY_TASKFINISH_GODANIMLLEVEL,			//s���޵ȼ�
	
	EVENT_ENTITY_TASKFINISH_CLIMBTOWER,				//����

	EVENT_ENTITY_TASKFINISH_GOLD,					//�����ٴ���
	
	EVENT_ENTITY_TASKFINISH_BATTLEANYDUNGEON,        //��ս���⸱�����

	EVENT_ENTITY_TASKFINISH_WORLDBOSS,               //�μ�����BOSS���
	
	EVENT_ENTITY_TASKFINISH_JOINCAMPBATTLE,			//�μ���Ӫս���

	EVENT_ENTITY_TASKFINISH_GETHERO,               //��ļӢ�����

	EVENT_ENTITY_TASKFINISH_GODANIMALTRAIN,			//��������

	EVENT_ENTITY_TASKFINISH_FIGHTSOULTRAIN,				//�������

	EVENT_ENTITY_TASK_HAVEREWARD,					//��������콱

	EVENT_ENTITY_TASK_HEROLEVELUP,					//Ӣ������

	EVENT_ENTITY_TASK_PLAYGIRL,						//��Ϸ���� 

	EVENT_ENTITY_TAKS_SOULQUALITY,					//���Ʒ��

	EVENT_ENTITY_TASK_FightGoldMonster,  				//��ɱԪ����

	EVENT_ENTITY_TASK_FightHeroExpMonster,				//��ɱ��Ϊ��

	EVENT_ENTITY_TASK_FightHeroMonster,					//��ɱӢ�۹�

	EVENT_ENTITY_ITEMCHG, 

	EVENT_ENTITY_TASK_HEROSKILL_LEVELUP,				//��������	

	EVENT_ENTITY_TASK_CRUSH_DREAMLAND_SCENE,			//ͨ������þ��ؿ�

	EVENT_ENTITY_ZIBAO, // �Ա�

	EVENT_ENTITY_TASK_SILVER_RES_LEVELUP,			//ͭ������

	EVENT_ENTITY_TASK_HEROEXP_RES_LEVELUP,			//��Ϊ������

	EVENT_ENTITY_PASSSCENE_COUNT,   					//ͨ�عؿ���

	EVENT_ENTITY_YAOQIANSHU_USETIMES,						//ҡǮ��ʹ�ô���

	EVENT_ENTITY_TASK_MANOR_HARVERST,					//����ջ�

	EVENT_ENTITY_TASK_MANOR_WuHunJiLian,					//��������

	EVENT_ENTITY_TASK_MANOR_ITEMDaZao,					//��Ʒ����

	EVENT_ENTITY_TASK_GIVE_Strength,						//��������

	EVENT_ENTITY_ADDHEROSOUL_FROMHERO,   // ���Ӣ�ۻ������¼�֪ͨ

	EVENT_ENTITY_TASK_ARENA_BATTLE,		//�μӾ�����

	EVENT_ENTITY_TASK_HEROSOUL_LEVEL,	//����ȼ�

	EVENT_ENTITY_TASK_TIEJIANGPU_LEVEL, 	//�����̵ȼ�

	EVENT_ENTITY_TASK_EQUIPLOVEQUIP,		//װ��ϲ��Ʒ

	EVENT_ENTITY_TASK_HEROQUALITY,		//Ӣ��Ʒ��

	EVENT_ENTITY_TASK_FORMATION,			//����

	EVENT_ENTITY_SAVEMONEY, // ��ֵ�ɹ�
};

typedef PropertySet EffectContext;


struct EventArgs_FightPropChg
{
	EventArgs_FightPropChg():iPropID(0), iChgValue(0), iValue(0), bReboundDamage(false), effectCtx(NULL), bRelive(false), bFilledResult(false){}

	HEntity hEventTrigger;
	HEntity hEntity;
	HEntity hGiver;
	int iPropID;
	int iChgValue;
	int iValue;
	bool bReboundDamage; // �Ƿ񷴵��˺�
	const EffectContext* effectCtx;
	bool bRelive;
	bool bFilledResult; // �Ƿ��Ѿ������Result��ս�����ֹ�ظ����
};


struct EventArgs_PropChange
{
	EventArgs_PropChange():iPropID(0), iType(0), iOldValue(0), 
		fOldValue(0.0), i64OldValue(0),iValue(0), fValue(0.0), i64Value(0){}
	
	HEntity hEntity;
	int iPropID;
	int iType;

	int iOldValue;
	float fOldValue;
	string strOldValue;
	Int64 i64OldValue;

	int iValue;
	float fValue;
	string strValue;
	Int64 i64Value;
};



struct EventArgsDamageCtx
{
	EventArgsDamageCtx():iHitResult(0), iResultDamage(0), effectCtx(NULL){}

	HEntity hEntity;
	HEntity hGiver;
	int iHitResult;
	int iResultDamage;
	const EffectContext* effectCtx;
};

// Ч��ϵͳ����
/*struct EventArgs_SkillResult
{
	EventArgs_SkillResult():bHitResult(0),bResultType(0),iSkillID(0), pResult(NULL), bEquipTriggerSkill(false), iVamPireHP(0){}
	HEntity hGiver;
	HEntity hEntity;
	Uint8 bHitResult;
	Uint8 bResultType;
	HEntity hNormalTarget;
	int iSkillID;
	HEntity hEventTigger;  // �����߾��,�����¼���˭���ϴ���
	void* pResult;
	bool bEquipTriggerSkill;
	int iVamPireHP;
	vector<HEntity> vamPireList;
};

struct EventArgs_Action
{
	EventArgs_Action():cActionType(0),pActionBuff(0) {}
	HEntity hGiver;
	HEntity hEntity;
	Uint8 cActionType;
	void* pActionBuff;
};

// ϵͳ/��ʵ�ĳ�����ʧ
struct EventArgs_Appear
{
	HEntity hEntity;
	HEntity hAppearEntity;
};

struct EventArgs_DissAppear
{
	HEntity hEntity;
	HEntity hDisAppearEntity;
};

struct EventArgs_Move
{
	HEntity hMoveEntity;
	void* pMoveContext;
};

struct EventArgs_ViewState
{
	HEntity hEntity;
	bool bIsFull;
};

struct EventArgs_EffectPropChange
{
	EventArgs_EffectPropChange():iPropID(0), iOrgPropID(0), iOrgDeltaValue(0), pEffectContext(NULL){}
	
	HEntity hEntity;
	int iPropID;
	int iOrgPropID;
	int iOrgDeltaValue;
	const PropertySet* pEffectContext;
};*/

#endif
