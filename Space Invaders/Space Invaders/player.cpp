//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
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

CPlayer::CPlayer()
{
	
}

CPlayer::~CPlayer()
{

}

bool
CPlayer::Initialise(const int _iScreenWidth)
{
	VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));
	m_iScreenWidth = _iScreenWidth;
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
    
	float fHalfPlayerW = m_pSprite->GetWidth() / 2.0;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if(m_pBullet == nullptr)
		{
			m_pBullet = new CBullet();
			m_pBullet->Initialise(m_fX, m_fY - 15, -260.0);
		}
		
	}
	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPlayerW;
	}
	else if (m_fX + fHalfPlayerW >= m_iScreenWidth)
	{
		m_fX = m_iScreenWidth - fHalfPlayerW;
	}
	
	
	CEntity::Process(_fDeltaTick);
}

CBullet * CPlayer::GetBullet()
{
	return m_pBullet;
}

void CPlayer::SetBullet(CBullet * _pBullet)
{
	m_pBullet = _pBullet;
}
