//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: menubutton.h
// Description	: Header file for the menu button, all buttons use this
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__MENUBUTTON_H__)
#define __MENUBUTTON_H__

// Library Includes

// Local Includes
#include "entity.h"

class CMenuButton : public CEntity
{
public:
	CMenuButton(const float _iX, const float _iY, int _iSpriteIDB, int _iSpriteMaskIDB);
	~CMenuButton();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();

	virtual bool ChangeSprite(int _iSpriteIDB, int _iSpriteMaskIDB);

private:
	int m_iSpriteIDB;
	int m_iSpriteMaskIDB;
};

#endif    // __MENUBUTTON_H__

