/********************************************************************
author:    ��PropertyParser����
summary:	�������������ļ�,�Զ���������������ö��,��Ҫ�ֶ��޸ĸ��ļ�!
*********************************************************************/
#pragma once

NS_FM_BEGIN

enum EHeroPropertyIndex
{
	EHero_ID,	//ΨһID
	EHero_ObjectType,	//obj����
	EHero_HeroId,	//Ӣ��id
	EHero_Lvl,	//�ȼ�
	EHero_Anger,	//ŭ��
	EHero_LvlStep,	//�Ƚ�
	EHero_HeroExp,	//����
	EHero_HP,	//��ǰ����ֵ
	EHero_MaxHP,	//�������ֵ
	EHero_IsDead,	//�Ƿ�����
	EHero_InitAnger,	//ŭ��
	EHero_Att,	//����
	EHero_Hit,	//����
	EHero_Doge,	//����
	EHero_Knock,	//����
	EHero_AntiKnock,	//����
	EHero_Wreck,	//�ƻ�
	EHero_Block,	//��
	EHero_Armor,	//����
	EHero_SunderArmor,	//�Ƽ�
	EHero_Skill,	//���⼼��
	EHero_FormationPos,	//����λ��
	EHero_FightValue,	//ս��
	EHero_HasFightSoul,	//�Ƿ�Я�����
	EHero_Price,	//���ۼ�λ
	EHero_HasEquip,	//�Ƿ�Я��װ��
	EHero_Quality,	//Ʒ��
	EHero_Def,	//����
};

enum EBagItemPropertyIndex
{
	EBagItem_ObjId,	//ΨһID
	EBagItem_Count,	//����
	EBagItem_CombineNeedCount,	//�ϳ���Ҫ������
};

enum EFightSoulPropertyIndex
{
	EFightSoul_ObjID,	//ΨһID
	EFightSoul_Exp,	//����
	EFightSoul_NextLvExp,	//��һ������
	EFightSoul_Pos,	//λ��
	EFightSoul_Lock,	//����
	EFightSoul_Lvl,	//�ȼ�
	EFightSoul_HP,	//����
	EFightSoul_InitAnger,	//ŭ��
	EFightSoul_Att,	//����
	EFightSoul_Hit,	//����
	EFightSoul_Doge,	//����
	EFightSoul_Knock,	//����
	EFightSoul_AntiKnock,	//����
	EFightSoul_Wreck,	//�ƻ�
	EFightSoul_Block,	//��
	EFightSoul_Armor,	//����
	EFightSoul_SunderArmor,	//�Ƽ�
};

enum EPlayerPropertyIndex
{
	EPlayer_ObjId,	//id
	EPlayer_Lvl,	//�ȼ�
	EPlayer_Flag,	//��־λ
	EPlayer_Exp,	//����
	EPlayer_MaxExp,	//��ǰ�����
	EPlayer_Silver,	//��Ϸ��
	EPlayer_Gold,	//Ԫ��
	EPlayer_Honor,	//����
	EPlayer_FSChipCount,	//�����Ƭ
	EPlayer_FormationLimit,	//������������
	EPlayer_FightValue,	//ս��
	EPlayer_Tili,	//����
	EPlayer_Vigor,	//����
	EPlayer_TiliMax,	//�������ֵ
	EPlayer_HeroConvertCount,	//Ӣ�۵���ת������
	EPlayer_HeroExp,	//��Ϊ
	EPlayer_VIP,	//VIP�ȼ�
	EPlayer_FunctionMask,	//���ܱ�־λ
	EPlayer_VipLevel,	//VIP�ȼ�
	EPlayer_VipExp,	//VIP��ǰ����
	EPlayer_VipLevelUpExp,	//VIP�¼�����
	EPlayer_FunctionNotice,	//��ʾ������־λ
	EPlayer_HeadType,	//ͷ������
	EPlayer_HeadId,	//ͷ��ID
	EPlayer_LeftPhyStrength,	//�ѹ������
	EPlayer_IsShowFirstPay,	//�Ƿ���ʾ�׳�
	EPlayer_LegionName,	//��������
};

enum EGodAnimalPropertyIndex
{
	EGodAnimal_ObjId,	//ΨһID
	EGodAnimal_Level,	//�ȼ�
	EGodAnimal_LevelStep,	//�Ƚ�
	EGodAnimal_IsActive,	//�Ƿ��Ѿ���ս
};

enum EEquipPropertyIndex
{
	EEquip_ObjID,	//ΨһID
	EEquip_Pos,	//λ��
	EEquip_SuitID,	//��װID
	EEquip_SellMoney,	//���ۼ۸�
	EEquip_LvlLimit,	//�ȼ�
	EEquip_HP,	//����
	EEquip_InitAnger,	//ŭ��
	EEquip_Att,	//����
	EEquip_Hit,	//����
	EEquip_Doge,	//����
	EEquip_Knock,	//����
	EEquip_AntiKnock,	//����
	EEquip_Wreck,	//�ƻ�
	EEquip_Block,	//��
	EEquip_Armor,	//����
	EEquip_SkillDamage,	//�����˺�
	EEquip_SunderArmor,	//�Ƽ�
};

NS_FM_END
