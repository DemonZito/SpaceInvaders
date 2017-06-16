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

#if !defined(__EXPLOSION_H__)
#define __EXPLOSION_H__

// Library Includes

// Local Includes
#include "entity.h"

class CExplosion : public CEntity
{
public:
	CExplosion(const float _iX, const float _iY);
	~CExplosion();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};

#endif    // __EXPLOSION_H__

