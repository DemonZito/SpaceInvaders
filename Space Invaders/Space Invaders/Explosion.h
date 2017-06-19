//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Explosion.h
// Description	: Header file for the explosions, visual enhancers created after stuff blows up.
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
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
	virtual ~CExplosion();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};

#endif    // __EXPLOSION_H__

