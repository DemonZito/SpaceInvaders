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

// This Includes
//#include "bullet.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemyBullet::CEnemyBullet()
	: m_fVelocityY(0.0f)
{
	m_pSprite = nullptr;
}

CEnemyBullet::~CEnemyBullet()
{

}

bool
CEnemyBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
	const int iMask = IDB_BULLETMASK;

	int iSprite = IDB_BULLETS;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(8);
	m_pAnim->SetSpeed(0.05f);
	m_pAnim->AddFrame(16);
	m_pAnim->AddFrame(24);

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityY = _fVelocityY;

	CEntity::m_pAnim->SetDestSizeW(16);
	CEntity::m_pAnim->SetDestSizeH(32);

	return (true);
}

void
CEnemyBullet::Draw()
{
	CEntity::Draw();
}

void
CEnemyBullet::Process(float _fDeltaTick)
{
	m_fY += m_fVelocityY * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

float
CEnemyBullet::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CEnemyBullet::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

float
CEnemyBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}
