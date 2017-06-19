//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: clouds.cpp
// Description	: Holds how the ambient clouds at the back of the window move and their sprite
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "clouds.h"



CClouds::CClouds(const float _iX, const float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


CClouds::~CClouds()
{
}

bool
CClouds::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(IDB_CLOUDS, IDB_CLOUDSMASK));
	CEntity::m_pSprite->SetDestSizeW(800);
	CEntity::m_pSprite->SetDestSizeH(30);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CClouds::Process(float _fDeltaTick)
{
	m_fX += 10.0f * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
}

void
CClouds::Draw()
{
	CEntity::Draw();
}
