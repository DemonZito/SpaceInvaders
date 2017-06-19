//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: mothership.h
// Description	: Header file for the mothership, the ship that randomly appears at the top of the screen
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__MOTHERSHIP_H__)
#define __MOTHERSHIP_H__

// Library Includes
#include <vector>
// Local Includes
#include "enemy.h"


// Types

// Constants

// Prototypes

class CMotherShip : public IEnemy
{
	// Member Functions
public:
	~CMotherShip();
	bool Initialise();
	void Draw();
	void Movement(float _fDeltaTick);


};


#endif    // __BRICK_H__

