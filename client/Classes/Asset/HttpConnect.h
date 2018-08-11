/********************************************************************
created:	2013-10-15
author:		SXH
summary:	�����汾���
*********************************************************************/
#pragma once
#include "FmConfig.h"
#include "cocos2d.h"
#include "FileMgr.h"
#include "cocos-ext.h"


//#define USE_ZIPRES 1

USING_NS_CC;

NS_FM_BEGIN


class HttpConnect:public CCNode
{
public:
	SINGLETON_MODE( HttpConnect );
public:
	HttpConnect();
	virtual ~HttpConnect();

	void RequestUrlFile(const char* url,const char* tag);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
};


NS_FM_END
