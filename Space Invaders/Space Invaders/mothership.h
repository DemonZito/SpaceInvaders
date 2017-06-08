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

	bool Initialise();
	void Draw();
	void Movement(float _fDeltaTick);


};


#endif    // __BRICK_H__

