/********************************************************************
created:	2014-02-28
author:		pelog
summary:	�����ڵĶ���
*********************************************************************/
#pragma once

#include "FmEntity.h"
#include "FmGeometry.h"
#include "Numeric/EquipData.h"

NS_FM_BEGIN
class Equip;

class EquipBag : public Component
{
private:
	vector<Equip*> m_equips;
	int	m_containerType;
public:
	vector<Equip*>& GetEquipList(){return m_equips;}
	EquipBag(Entity* entity, int type);

	Equip* GetEquipByPos(int pos)
	{
		if (pos < 0 || pos >= m_equips.size())
		{
			return NULL;
		}

		return m_equips[pos];
	}

	int GetSellMoneyByQuality(int quality);

	void GetEquipListByWearPos(vector<Equip*>& list, int pos);

	int GetEquipCount( int id, Equip* equip );

	bool EquipIsInBag(Equip* equip);

	void GetEquipList(vector<Equip*>& list);

	//��÷���Ҫ���װ���б�
	void getSizeUpEquip(vector<Equip *> &list,const int equipType,const int heroType);
	//hero ʹ�õ� 
	bool HeroEquipIsWear(const int pos);
	//�Ƿ��п��Դ�����װ��
	bool HeroHasCanEquip(const int equipType,const int heroType);
	//�Ƿ��п��Դ�����װ�� ����õ�
	bool PlayerCanEquip();
    //����objectID ��ȡװ��
	Equip *getEquipByObjectId(const int objectId);
};

//��������
struct AddAttributes
{
	int lifeattId;
	int lifeattValue;
	AddAttributes(){lifeattId = 0;lifeattValue = 0;}
};

class Equip : public Entity
{
protected:
	Equip( uint8 entityType, uint entityId, const string& name );
	stEquipData* m_data;
	AddAttributes addattribute;
public:
	virtual ~Equip();

	// �����ӿ�
	static Entity* Create( uint entityId, const string& entityName, EntityCreateOpt* createOpt );
	static void InitInterface();
	void SetData(stEquipData* data){m_data = data;}
	stEquipData* GetData(){return m_data;}
	void setAddAttribute(const int lifeattId,const int lifeattValue);
	AddAttributes getAddAttribute()
	{
		return addattribute;
	}
};

NS_FM_END