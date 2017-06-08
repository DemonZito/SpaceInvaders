//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "enemy.h"

// This include
#include "AnimatedSprite.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAnimatedSprite::CAnimatedSprite()
: m_fFrameSpeed(0.0f)
, m_fTimeElapsed(0.0f)
, m_iCurrentSprite(0)
{
}

CAnimatedSprite::~CAnimatedSprite()
{
	Deinitialise();
}

bool
CAnimatedSprite::Deinitialise()
{
	return (CSprite::Deinitialise());
}

bool
CAnimatedSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
	return (CSprite::Initialise(_iSpriteResourceID, _iMaskResourceID));
}

void
CAnimatedSprite::DrawAnimated()
{
	int iTopLeftX = m_vectorFrames[m_iCurrentSprite];
	int iTopLeftY = 0;

	int iW = GetFrameWidth();
	int iH = GetHeight()/2;

	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);

	//HDC hSpriteDC = CGame::GetInstance().GetSpriteDC();
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	//BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, iTopLeftX, iTopLeftY, SRCAND);

	StretchBlt( pBackBuffer->GetBFDC(),iX,iY,50,50,s_hSharedSpriteDC,iTopLeftX,iTopLeftY, iW,iH,SRCAND);

	SelectObject(s_hSharedSpriteDC, m_hSprite);

	//BitBlt(CGame::GetInstance().GetBackBuffer()->GetDC(), iX, iY, iW, iH, hSpriteDC, iTopLeftX, iTopLeftY, SRCPAINT);
	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, 50, 50, s_hSharedSpriteDC, iTopLeftX, iTopLeftY, iW, iH, SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObj);

	//CSprite::Draw();
}

void
CAnimatedSprite::Process(float _fDeltaTick)
{
	m_fTimeElapsed += _fDeltaTick;

	if (m_fTimeElapsed >= m_fFrameSpeed &&
		m_fFrameSpeed != 0.0f)
	{
		m_fTimeElapsed = 0.0f;
		++m_iCurrentSprite;

		if (m_iCurrentSprite >= m_vectorFrames.size())
		{
			m_iCurrentSprite = 0;
		}
	}

	CSprite::Process(_fDeltaTick);
}

void
CAnimatedSprite::AddFrame(int _iX)
{
	m_vectorFrames.push_back(_iX);
}

void 
CAnimatedSprite::SetSpeed(float _fSpeed)
{
	m_fFrameSpeed = _fSpeed;
}

void 
CAnimatedSprite::SetWidth(int _iW)
{
	m_iFrameWidth = _iW;
}

int 
CAnimatedSprite::GetWidth()
{
	return (m_iFrameWidth*2);
}

int CAnimatedSprite::GetFrameWidth()
{
	return (m_iFrameWidth);
}

int CAnimatedSprite::GetHeight()
{
	return (CSprite::GetHeight()*2);
}
