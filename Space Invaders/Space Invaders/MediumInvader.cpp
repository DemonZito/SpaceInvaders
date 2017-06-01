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
#include <vector>
// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "MediumInvader.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation


bool
CMediumInvader::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_MEDIUMINVADER, IDB_BRICKMASK));
	return (true);
}

int CMediumInvader::GetPoints()
{
	return 30;
}
