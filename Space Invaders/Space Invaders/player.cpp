//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: player.cpp
// Description	: The character the player controls. holds thier sprite, how they move and shoot, and life totals
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "bullet.h"

// This Include
#include "player.h"
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer():
	m_bHit(false)
{
	m_iHealth = 3;
}

CPlayer::~CPlayer()
{
	if (m_pBullet != nullptr)
	{
		delete m_pBullet;
		m_pBullet = 0;
	}
}

bool
CPlayer::Initialise(const int _iScreenWidth)
{
	VALIDATE(CEntity::Initialise(IDB_PLAYER, IDB_PLAYERMASK));
	CEntity::m_pSprite->SetDestSizeW(50);
	CEntity::m_pSprite->SetDestSizeH(50);
	m_iScreenWidth = _iScreenWidth;
	m_iBulletSpeed = -260.0;
    return (true);
}

void
CPlayer::Draw()
{
    CEntity::Draw();
}

void
CPlayer::Process(float _fDeltaTick)
{
    
	float fHalfPlayerW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 300.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 300.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if(m_pBullet == nullptr)
		{
			m_pBullet = new CBullet();
			m_pBullet->Initialise(m_fX, m_fY - 15, m_iBulletSpeed);
		}
		
	}
	if (m_fX - fHalfPlayerW <= 0)
	{
		m_fX = fHalfPlayerW;
	}
	else if (m_fX + fHalfPlayerW >= m_iScreenWidth)
	{
		m_fX = m_iScreenWidth - fHalfPlayerW;
	}
	
	
	CEntity::Process(_fDeltaTick);
}

void
CPlayer::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CPlayer::IsHit() const
{
	return (m_bHit);
}

void CPlayer::LoseLife()
{
	m_iHealth--;
}

int CPlayer::GetLives()
{
	return m_iHealth;
}

void CPlayer::SetHealth(int _iHealth)
{
	m_iHealth = _iHealth;
}

void CPlayer::SetBulletSpeed(float _iBulletSpeed)
{
	m_iBulletSpeed = _iBulletSpeed;
}

void CPlayer::DeleteBullet()
{
	if (m_pBullet != nullptr)
	{
		delete m_pBullet;
		m_pBullet = nullptr;
	}
	
}


CBullet * CPlayer::GetBullet()
{
	return m_pBullet;
}

void CPlayer::SetBullet(CBullet * _pBullet)
{
	m_pBullet = _pBullet;
}
