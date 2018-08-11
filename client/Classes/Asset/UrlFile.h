/********************************************************************
created:	2012-12-07
author:		SXH
summary:	��CCLayer��չ����Ҫ�ṩ��Ϸlayer���õ���Ч����������չ
*********************************************************************/
#pragma once
#include "FmConfig.h"
#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

NS_FM_BEGIN

enum E_UrlFileStatus
{
	E_UrlFileStatus_None,			//
	E_UrlFileStatus_Reqed,			//��������
	E_UrlFileStatus_RspError,		//���ش����Ӧ
	E_UrlFileStatus_RspOk,			//��ӦOk
	E_UrlFileStatus_TimeOout,		//��ʱ
};

class UrlFile
{
public:
	UrlFile();
	UrlFile(const char* tag);
	virtual ~UrlFile();
	void SetTagName(const char* tag){m_TagName = tag;};
	void SetMd5(const char* md){m_Md5 = md;};
	void SetFileSize(int size){m_Size = size;};

	const string& GetTagName(){return m_TagName;};
	const string& GetMd5(){return m_Md5;};
	int	GetFileSize(){return m_Size;};
	
	void SetRefresh(bool brefrsh){m_NeedRefresh = brefrsh;};
	bool NeedRefresh(){return m_NeedRefresh;};

	void SetDelete(bool del){m_NeedDel = del;};
	bool NeedDelete(){return m_NeedDel;};

	void SetPackRes(bool packfile) {m_isPcakRes = packfile;};
	bool IsPackRes() {return m_isPcakRes;};

private:
	std::string m_TagName;
	std::string	m_Md5;
	int		m_Size;
	bool	m_NeedRefresh;
	bool	m_NeedDel;
	bool	m_isPcakRes;
};
	
NS_FM_END