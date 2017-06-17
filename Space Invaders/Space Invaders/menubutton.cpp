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
#include "menubutton.h"



CMenuButton::CMenuButton(const float _iX, const float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


CMenuButton::~CMenuButton()
{
}

bool
CMenuButton::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(IDB_DEADEXPLOSION, IDB_DEADEXPLOSIONMASK));
	CEntity::m_pSprite->SetDestSizeW(50);
	CEntity::m_pSprite->SetDestSizeH(50);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CMenuButton::Draw()
{
	CEntity::Draw();
}
