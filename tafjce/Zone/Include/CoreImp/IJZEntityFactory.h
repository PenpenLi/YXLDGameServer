#ifndef __IJZENTITY_FACTORY_H__
#define __IJZENTITY_FACTORY_H__

struct LevelStepGrowCfg
{
	LevelStepGrowCfg():iLevelStep(0), iNeedProgress(0), iGrowParam(0), iBasePropParam(0), iNeedSoulCount(0), iNeedSilver(0), iExtraSoulCount(0){}

	int iLevelStep;
	int iNeedProgress;
	int iGrowParam;
	int iBasePropParam; // ������������ϵ��
	int iNeedSoulCount;
	int iNeedSilver;
	int iExtraSoulCount;
};

struct FunctionOpenDesc
{
	FunctionOpenDesc():iFunctionID(0), iErrorCode(0){}

	int iFunctionID;
	int iErrorCode;
};

struct CreateHeroDesc
{
	CreateHeroDesc():iHeroID(0), iFormationPos(0), iLevel(0), iLevelStep(0), iQuality(0){}

	int iHeroID;
	int iFormationPos;
	int iLevel;
	int iLevelStep;
	int iQuality;
};

class IJZEntityFactory
{
public:

	virtual ~IJZEntityFactory(){}

	// ����: ����������,���������Ĺ�������ڸ��Ե�λ����
	// ���ص�vector�б�size�ǹ̶���9��λ�ã�û�й�������0
	// ����: [iMonsterGrpID] ������ID
	virtual vector<HEntity> createMonsterGrp(int iMonsterGrpID) = 0;

	// ����: ��ѯ�Ƚ�����
	virtual const LevelStepGrowCfg* queryLevelStepCfg(int iLevelStep) = 0;

	// ����: ����Ƚ�
	virtual int calcLevelStep(int iProgress) = 0;

	// ����: ��ȡIEntityFactory �ӿ�
	virtual IEntityFactory* getEntityFactory() = 0;

	virtual int getGodAnimalLevelLimit(int iLevelStep) = 0;

	virtual int getVisibleMonsterID(int iMonsterGrpID) = 0;

	virtual IEntity* createMachine(const string& strAccount, const string& strName, const vector<CreateHeroDesc>& heroIDList) = 0;

	virtual const FunctionOpenDesc* getEnableFunctionData(int iLevel) = 0;

	virtual const FunctionOpenDesc* getFunctionData(int iFunction) = 0;

	virtual void calcHeroNewLevelExp(HEntity hHero, long ddAddExp, int& iNewLevel, int& iNewExp) = 0;

	virtual int calcHeroSumExp(int iLevel, int iCurExp) = 0;
};


#endif
