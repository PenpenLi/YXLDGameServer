#include "FmGodAnimal.h"
#include "FmEntityMgr.h"

GodAnimal::~GodAnimal(){

}
GodAnimal::GodAnimal( uint8 entityType, uint entityId, const string& name )
	:Entity(entityType,entityId,name)
	,m_GodAnimaldata(NULL)
{
	m_PropertySet.Init( PropertyDescMgr::GetInstance().Get( "GodAnimal" ) );
}
Entity* GodAnimal::Create( uint entityId, const string& entityName, EntityCreateOpt* createOpt )
{
	GodAnimal* entity = new GodAnimal(EEntityType_GodAnimal,entityId, entityName );
	return entity;
}

void GodAnimal::InitInterface()
{
	// ע����󴴽��ӿ�
	SEntityAlloc entityAlloc;
	entityAlloc.m_EntityCreator = GodAnimal::Create;
	EntityMgr::GetInstance().RegisterEntityAlloc( EEntityType_GodAnimal, entityAlloc );
}