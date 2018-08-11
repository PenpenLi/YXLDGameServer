/********************************************************************
created:	2012-12-09
author:		Fish (�ڹ�ƽ)
summary:	��ͼ��Layer
*********************************************************************/
#pragma once

#include "FmConfig.h"
#include "cocos2d.h"
//#include "Effect/FmEffect.h"

USING_NS_CC;

NS_FM_BEGIN
enum EMapLayerTag
{
	EMapLayerTag_TileMap = 1,
	EMapLayerTag_TileMidBg ,
	EMapLayerTag_TileBg,
	EMapLayerTag_CurEntitySocialNode,
	EMapLayerTag_SceneUi,
};

class MapLayer  : public CCLayer
{
public:
	static MapLayer *create(const char* file);
	//CREATE_FUNC(MapLayer);

	bool init(const char* file);

	//���������Ŀ������
	//void SetCameraDestPos(const CCPoint& pos);
	CCSize& GetMapSize(){return m_ScreenSize;}

	void changeNextMap(const char* file);
private:
	string m_file;
	CCSize m_ScreenSize;
};
NS_FM_END