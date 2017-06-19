//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: EnemyBullet.h
// Description	: Header file for the Life Counters, sprites that appear at the bottom of the screen to represent health
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__LIFECOUNT_H__)
#define __LIFECOUNT_H__

// Library Includes

// Local Includes
#include "entity.h"

class CLifeCount : public CEntity
{
public:
	CLifeCount(const int _iX, const int _iY);
	virtual ~CLifeCount();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};
# endif

