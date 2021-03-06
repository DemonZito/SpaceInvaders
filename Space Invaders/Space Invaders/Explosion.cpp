//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Explosion.cpp
// Description	: Holds the sprite for explosion. Triggers after stuff blows up
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "Explosion.h"



CExplosion::CExplosion(const float _iX, const float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


CExplosion::~CExplosion()
{
}

bool 
CExplosion::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(IDB_DEADEXPLOSION, IDB_DEADEXPLOSIONMASK));
	CEntity::m_pSprite->SetDestSizeW(50);
	CEntity::m_pSprite->SetDestSizeH(50);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CExplosion::Draw()
{
	CEntity::Draw();
}
