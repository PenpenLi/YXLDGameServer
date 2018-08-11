/********************************************************************
created:	2013-3-13
author:		SXH
summary:	�ļ���Դ����
*********************************************************************/
#pragma once
#include "FmConfig.h"
#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

NS_FM_BEGIN

class UrlFile;

typedef map<string,UrlFile*> UrlFileMap;

class FileMgr:public CCNode,public CCSAXDelegator
{
public:
	static bool VersionMatched(const FileMgr* fm1,const FileMgr* fm2);

	static bool UnCompress(const char* filename,const char* path);
	static bool createDirectory(const char *path);
public:
	FileMgr();
	virtual ~FileMgr();

	void Clear();
	//plist �ṹ����
	// implement pure virtual methods of CCSAXDelegator
	void startElement(void *ctx, const char *name, const char **atts);
	void endElement(void *ctx, const char *name);
	void textHandler(void *ctx, const char *ch, int len);

	//�����ļ������ʼ������
	bool InitLocalMgr(const char* writePath,const char* resConfigName);
	//�����ļ������ʼ��
	bool LoadLocalConfig();

	void SetResUrl(const char* resUrl);

	//�������ļ������ʼ��
	bool InitServerMgr(const char* resUrl,const char* versionNumName,const char* resConfigName);
	//�������ļ�������ȡ�汾��
	bool RequestVersionNum();
	//�������ļ�������ȡ��Դ����
	bool RequestResConfig();

	//�Ƿ��ȡ���汾��
	bool HasGetVersionNum();

	bool IsPreapred(){return m_Prepared;};

	bool SynWithFileMgr(FileMgr* fmserver);

	//�ϲ����ڳ��������Դ
	bool MergeWithFileMgr(FileMgr* fmApp);

	//���°�װ��������ԭ�����ļ�
	bool CheckPackRes();

	UrlFile* GetFileByName(const char* name);

	const UrlFileMap& GetFileMap();

	bool ActiveNextRequest();
	bool StartRequest();
	bool IsRequestFinished(){return m_IsInRequest == false;};

	bool OnLoadFinished();

	bool SavingConfigFile(bool finishSave=true);

	int GetTotalDownSize(){return m_TotalLoadByteSize;};
	int GetCurDownSize(){return m_CurLoadByteSize;};

	bool CodeVersionMatched(const string codeVersion);

	void SetPrepare(bool pre){m_Prepared = pre;};

	bool CodeVersionIsLowerThan(const string codeVersion);

private:
	bool InitFilesWithBuff(const char* buffer);
	bool InitVersionNumWithBuff(const char* buffer);
	void RequestUrlFile(const char* url,const char* tag);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
private:
	//���غͷ���˹���
	UrlFileMap	m_FileMap;
	bool		m_Prepared;
	string		m_Version;
	string		m_UpdateVersion;
	bool		m_VersionPreapred;

	string		m_CodeVersion;

	//��Դ�����ļ���
	string		m_ConfigName;
	//�汾���ļ���
	string		m_VersionFileName;

	//���ش洢·��
	string		m_WritePath;
	//��������URL
	string		m_ResUrl;

	bool		m_IsInRequest;
	int			m_TotalLoadByteSize;
	int			m_CurLoadByteSize;
	
	cc_timeval	m_LoadStartTime; 
	cc_timeval	m_LastSaveTime; 
};

NS_FM_END
