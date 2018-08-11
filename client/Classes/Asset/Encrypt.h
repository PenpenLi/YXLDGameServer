/********************************************************************
created:	2013-07-17
author:		Fish (�ڹ�ƽ)
summary:	���ܽ���
*********************************************************************/
#pragma once

#include "FmIOUtil.h"

NS_FM_BEGIN

class Encrypt
{
public:
	// ��ȡ�����ļ�
	static uint8* GetFileData( const char* fileName, const char* mode, uint* dataSize );

	// �����������
	static bool SaveFileData( const char* fileName, const uint8* data, uint dataSize );

	// �����ļ�
	static bool EncryptFile( const char* fileName, const char* encryptFileName );



	//�ļ�ͷ����ֽ�0xcc����ʾPNG�ļ�
	static bool MaskFile(const char* fileName,const char* hidenFileName );

	// ���汻���ε��ļ�
	static bool SaveMaskData( const char* fileName, const uint8* data, uint dataSize );

};

NS_FM_END