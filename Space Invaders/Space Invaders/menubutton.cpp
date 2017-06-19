//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: menubutton.cpp
// Description	: holds sprite for menu buttons.
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "menubutton.h"



CMenuButton::CMenuButton(const int _iX, const int _iY, int _iSpriteIDB, int _iSpriteMaskIDB)
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
