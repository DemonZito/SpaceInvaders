//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: bullet.cpp
// Description	: The players bullets holds its sprite and how it moves in level
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "AnimatedSprite.h"

// This Includes
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation
bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
	const int iMask = IDB_BULLETMASK;

	int iSprite = IDB_BULLETS;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(8);
	m_pAnim->SetSpeed(0.05f);
	m_pAnim->AddFrame(0);
	m_pAnim->AddFrame(8);

    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityY = _fVelocityY;

	CEntity::m_pAnim->SetDestSizeW(16);
	CEntity::m_pAnim->SetDestSizeH(32);

    return (true);
}

CBullet::~CBullet()
{
	if (m_pAnim != nullptr)
	{
		delete m_pAnim;
		m_pAnim = 0;
	}
}

//CBullet::~CBullet()
//{
//}

void
CBullet::Draw()
{
	CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick)
{
	m_fY += m_fVelocityY * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

float 
CBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

float 
CBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
