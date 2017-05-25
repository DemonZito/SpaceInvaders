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
CPlayer::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

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
    
	float fHalfPaddleW = m_pSprite->GetWidth() / 2.0;

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
		if(m_pBall == nullptr)
		{
			m_pBall = new CBullet();
			m_pBall->Initialise(m_fX, m_fY - 15, 0, -260.0);
		}
		
	}
	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 385)
	{
		m_fX = 385-fHalfPaddleW;
	}
	
	
	CEntity::Process(_fDeltaTick);
}

CBullet * CPlayer::GetBullet()
{
	return m_pBall;
}

void CPlayer::SetBullet(CBullet * _pBullet)
{
	m_pBall = _pBullet;
}
