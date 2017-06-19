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
	CEntity::m_pSprite->SetDestSizeW(400);
	CEntity::m_pSprite->SetDestSizeH(30);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CClouds::Process(float _fDeltaTick)
{
	m_fX += 1.0f * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
}

void
CClouds::Draw()
{
	CEntity::Draw();
}
