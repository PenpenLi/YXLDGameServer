/********************************************************************
created:	2012-12-07
author:		pelog (�Ƴ�)
summary:	�ͻ��˵����
*********************************************************************/
#pragma once
#include "FmEntity.h"
#include "NetWork/GameServer.pb.h"
#include "FmBagItem.h"
#include "FmGodAnimal.h"
#include "HeroSoul/FmHeroSoul.h"
#include "FmPlatform.h"


NS_FM_BEGIN
class FightSoulBag;
class Hero;
class EquipBag;

class Player : public Entity
{
public:
	class PlayerCreateOpt : public EntityCreateOpt
	{
	public:
		bool m_IsLocalPlayer;

		PlayerCreateOpt()
		{
			m_IsLocalPlayer = false;
		}
	};
protected:
	bool	m_IsLocalPlayer;	// �Ƿ��Ǳ������
	int	m_PreDupScene;		// �������ǰһ������������

	vector<uint> m_HeroList;
	vector<uint> m_FormationList; //0��ʾ��Ӣ��
	vector<BagItem*> m_playerBagItems;//��ұ�������

	vector<GodAnimal*> m_GodAnimalList;		//�����б�

	int	m_fightValue;
	int	m_formationLimit;
	map<uint,uint> m_tempPlayerBagItems;

protected:
	Player( uint8 entityType, uint entityId, const string& name, bool isLocalPlayer );
public:
	virtual ~Player();

	// �����ӿ�
	static Entity* Create( uint entityId, const string& entityName, EntityCreateOpt* createOpt );

	// ע����󴴽��ӿ�
	static void InitInterface();

	// ������ұ��
	bool IsLocalPlayer() const { return m_IsLocalPlayer; }
	void SetLocalPlayer( bool isLocalPlayer ) { m_IsLocalPlayer=isLocalPlayer; }

	// ����
	virtual void Update( uint delta );

	// �������
	//Quest* GetQuest();

	// ����
	//PlayerBag* GetBags();
	FightSoulBag* GetFightSoulBags();

	// �ƶ���������ĳ��entity��λ��
	//void MoveToTargerEntity( SceneEntity* targetEntity );

	// ��ȡ���Ӣ��
	Hero* GetPlayerHero();

	uint GetLevel();

	vector<uint>& GetHeroList(bool isfresh = true);
	void GetCanSummonHeroList(vector<uint>& cansummomHeroList);
	void GetNotSummonHeroList(vector<uint>& notcansummomHeroList);
	void GetCanSummonHeroAndHeroList(vector<uint>& summondHeroList);
	vector<uint>& GetFormationList(){
		return m_FormationList;
	}
	Bag* GetPlayerBag();
	vector<GodAnimal*>& GetGodAnimalList() { 
		return m_GodAnimalList;
	}
	vector<GodAnimal*> GetCanInheritGodAnimal(GodAnimal* animal);
	GodAnimal* GetGodAnimalByDwObject(int dwobject);
	//�趨��ս���ޣ���ս����Ĭ�Ϸ��ڵ�һ��λ��
	void SetGodAnimalActive(int dwObjctId);
	//��ȡ��ǰδ��õ�����
	void GetPlayerNotHave(vector<int>& nothavegodanimal);
	//������������޻��ǵ�����
	void GetHaveSoulGodAnimal(vector<int>& havesoulgodanimal);
	//��ȡӢ��δ�����б�Ӣ�ۻỻ
	void GetNotExpeditionHeroList(vector<uint>& notExpeditionHeroList);
	//���Ӣ��δ�����б����򣩣�Ӣ�۳���
	void GetNotExpeditionHeroListByHeroSell(vector<uint>& notExpeditionHeroList);
	void GetHeroAscendingOrderList(vector<uint>& HeroAscendingOrderLis,uint entityId,uint objId);
	void RemoveHeroFromList(uint entityId);
	bool IsInFormation(Hero* hero);
	int GetHeroFormationPos(Hero* hero);

	//��ó���Ӣ��
	void GetFormationHeroList(vector<uint>& FormationHeroList);

	// Ӣ����������
	void EraseHerolistInHeroBatchSell(vector<uint>& heroBatchSellList,uint ObjectId);
	void AddHerolistInHeroBatchSell(vector<uint>& heroBatchSellList,uint ObjectId);

	//����heroid �Ƿ�ͳ����б��е�Ӣ��һ�� 
	bool IsSameAsInforMationHero(const uint HeroId);

	Hero* GetHeroByObjId(uint objId);
	int GetHeroIndexByObjId(uint objId);

	int GetHeroInFormationCount();
	void InitFormationList();
	static void HeroUpdate( int iCmd, GSProto::SCMessage& pkg );
	static void HeroDel( int iCmd, GSProto::SCMessage& pkg );
	static void HeroBatchDel(int iCmd,GSProto::SCMessage& pkg );
	static void FSContainerChg( int iCmd, GSProto::SCMessage& pkg );

	static void GodAnimalUpdate(int iCmd, GSProto::SCMessage& pkg);
	static void EquipContainerChg( int iCmd, GSProto::SCMessage& pkg );

	static void EquipQuery( int iCmd, GSProto::SCMessage& pkg );
	static void HeroSoulChg(int iCmd,GSProto::SCMessage& pkg);
	static void HeroTallenSkillChg(int iCmd,GSProto::SCMessage& pkg);
	//bool PointIsInRect(FmPoint point, FmRect rect);
	
	// ����������
	//void SetName( const char* name );
	void HerolistSort();
	EquipBag* GetEquipBags();
	Bag* GetPlayerMaterail();
	//�жϵ�ǰ�����Ƿ����� 
	bool GodAnimalisHaveByAnimalId(const int godanimalId);

	//��������
	void sortGodAnimalWithId(vector<int>& AllgodanimalId);

	const uint GetGodAnimalWithId(const int godanimalId);
	GodAnimal* GetGodAnimalByAnimalId(const int godanimalId);

	//����
	HeroSoulBag* GetPlayerHeroSoul();
	//��õ�ǰ���ǵĸ���
	int GetPlayerHeroSoulCountById(const int herosoulID);
	//�жϷ��������µ������ӻ��Ǽ��� ����Ļ���һ����������ϵ�
	bool PlayerHeroSoulIsAdd(const int herosoulID,const int count);
	//�жϷ��������µ�������еĻ���û��
	bool PlayerHeroSoulIsHave(const int herosoulId);

	//�жϵ�ǰӢ���Ƿ�����ٻ�
	bool PlayerHeroCanSummon(int heroId);
	void GetPlayerCanSummonHeroList(vector<uint> &canSummonHeroList);
	bool PlayerHeroCannotSummon(int heroId);

	void OperatorHeroSoulByShoulID(const int herosoulID,const int count);

	//�ж�Ӣ���Ƿ���ϲ��Ʒ
	bool PlayerHeroHaveFavorite();
	//���ϲ��Ʒ�ַ���
	void GetHeroQualityFavoriteItemId(std::string src,vector<int >& itemId);
	//����Ƿ���ϲ��Ʒ
	bool PlayerHaveFavorite(const int heroObjectId , const int itemID);
	//���Ӣ��ϲ��ƷitemID
	void GetPlayerFavoriteItemID(vector<int >& itemID,Hero *hero);
	//����Ƿ��Ѿ�װ��ϲ��Ʒ
	bool PlayerHaveEquipFavorite(const int heroObjectId,const int itemId);
	//���Ӣ��ϲ��Ʒstring
	string GetPlayerHeroFavorite(const int quality,const int heroId);
	//�ж�Ӣ����װ����ϲ��Ʒ�Ǽ���λ��
	int GetPlayerHeroFavoritePosition(const int herofavoriteId,const int heroObjectId);
	int GetPlayerHeroFavoritePositionByHero(const int herofavoriteId,Hero*hero);
	//��������ϲ��Ʒ�Ƿ�����Ҫ��
	bool PlayerHeroFavoriteCanAdmix(const int herofavoriteId);
	//���ϲ��Ʒ
	void PlayerHeroFavoriteCheck();

	//��ʱ������Ϣ��ʼ��
	void InitTempPlayerBagItemWithFavorite();
	//��鵱ǰ��ʱ�����ĸ���
	int CheckTempPlayerBagItemCount(const int itemId);
	//������ʱ����
	void ChangeTempPlayerBagItem(const int itemId,const int number);
	//��鵥����ϲ��Ʒ
	void PlayerHeroFavoriteCheckByObjectId(const int heroObjectId);
	//װ��ϲ��Ʒ
	void EquipHeroFavorite(const int herofavoriteId,Hero *hero,const int pos);
	void EquipHeroFavoriteByHeroObject(const int herofavoriteId,const int heroObjectId,const int pos);
	//�ж�Ӣ���Ƿ�ϲ��Ʒ��������
	bool HeroHaveAllEquipFavorite(const int heroObjectId);
	//����hero ϲ��Ʒ
	void UpdateHeroFavoriteByHeroObjectId(const int heroObjectId);

	//���ϲ��Ʒ�ϳ��������Item
	void GetHeroFavoriteSummondItemId(const int herofavoriteId,vector<int> &favoriteId,vector<int > &favoriteMaterialNumber);
	//�ж�ϲ��Ʒ�Ƿ���Ժϳ�
	bool HeroFavoriteCanSummondByFavoriteId(const int heroFavoriteId);
	//�����ȱ����Ʒ
	int HeroFavoriteNotHave_ByCanSummondByFavoriteId(const int heroFavoriteId);
	//�ж�ϲ��Ʒ�Ƿ�Ϊ����ϲ��Ʒ
	bool HeroFavoriteIsBaseFavorite(const int heroFavoriteId);
	//�õ�ϲ��Ʒ������
	void GetHeroFavoriteNatureByItemId(vector<string>& favoriteNature,const int itemId);
	

	//�츳����
	void UpdateHeroTallentSkillData(const uint32 heroObjId, const int32 tallenSillID,const int tallSkilllevel,const bool tallSkillCanup);
	bool CheckHeroTallentCanUpOrAct();

	//��ȡʱ�� 
	long getCurrentTime();
	//���ʱ��ķ���
	int getCurrentMinTime();
	//�жϵ�ǰʱ���Ƿ���ָ��ʱ�����
	bool IsInCurTime(long timeBegin,long timeEnd);

   // ��ȡ�·�
	int getMoth();
	//
	int getDelayTime(const int hour , const int min);
};

NS_FM_END