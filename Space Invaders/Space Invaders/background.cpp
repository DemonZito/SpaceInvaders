//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: background.cpp
// Description	: Holds the background sprite
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"

// This Include
#include "background.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

bool
CBackGround::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BACKGROUND, IDB_BACKGROUNDMASK));
	//CEntity::SetWidth(CEntity::GetWidth() * );
	//CEntity::SetHeight(CEntity::GetHeight() * 10);

	return (true);
}

void
CBackGround::Draw()
{
	CEntity::Draw();
}

void
CBackGround::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
