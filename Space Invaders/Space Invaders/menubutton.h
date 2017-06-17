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
#pragma once

#if !defined(__MENUBUTTON_H__)
#define __MENUBUTTON_H__

// Library Includes

// Local Includes
#include "entity.h"

class CMenuButton : public CEntity
{
public:
	CMenuButton(const float _iX, const float _iY);
	~CMenuButton();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};

#endif    // __MENUBUTTON_H__

