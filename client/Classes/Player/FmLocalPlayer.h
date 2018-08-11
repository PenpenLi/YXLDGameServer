/********************************************************************
created:	2012-12-09
author:		Fish (�ڹ�ƽ)
summary:	������ҵ���ؽӿ�
*********************************************************************/
#pragma once

#include "FmConfig.h"
#include "FmPlayer.h"

NS_FM_BEGIN

class LocalPlayer
{
protected:
	Player*	m_Player;	// ������Ҷ���
public:
	LocalPlayer();
	virtual ~LocalPlayer();

	SINGLETON_MODE( LocalPlayer );

	void SetPlayer( Player* player ) { m_Player = player; }
	Player* GetPlayer() { return m_Player; }

};

static Player* GetLocalPlayer()
{
	return LocalPlayer::GetInstance().GetPlayer();
}

NS_FM_END