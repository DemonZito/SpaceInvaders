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
#include "LifeCount.h"



CLifeCount::CLifeCount(const float _iX, const float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


CLifeCount::~CLifeCount()
{
}

bool
CLifeCount::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(IDB_LIFE, IDB_LIFEMASK));
	CEntity::m_pSprite->SetDestSizeW(12);
	CEntity::m_pSprite->SetDestSizeH(12);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CLifeCount::Draw()
{
	CEntity::Draw();
}
