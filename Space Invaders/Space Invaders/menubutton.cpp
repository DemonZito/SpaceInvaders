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



CMenuButton::CMenuButton(const float _iX, const float _iY, int _iSpriteIDB, int _iSpriteMaskIDB)
{
	m_fX = _iX;
	m_fY = _iY;
	m_iSpriteIDB = _iSpriteIDB;
	m_iSpriteMaskIDB = _iSpriteMaskIDB;
}


CMenuButton::~CMenuButton()
{
}

bool
CMenuButton::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(m_iSpriteIDB, m_iSpriteMaskIDB));

	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CMenuButton::Draw()
{
	CEntity::Draw();
}

bool CMenuButton::ChangeSprite(int _iSpriteIDB, int _iSpriteMaskIDB)
{
	m_iSpriteIDB = _iSpriteIDB;
	m_iSpriteMaskIDB = _iSpriteMaskIDB;
	VALIDATE(m_pSprite->Initialise(m_iSpriteIDB, m_iSpriteMaskIDB));
	return true;
}
