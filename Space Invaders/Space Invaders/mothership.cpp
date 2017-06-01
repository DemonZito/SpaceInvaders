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

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "mothership.h"

// Static Variables

// Static Function Prototypes

// Implementation

CMotherShip::CMotherShip(const int _iDirection)
	: m_bHit(false),
	m_fTime(0),
	m_fSpeed(1.0f),
	m_bWallHit(false)
{
	m_iDirection = _iDirection;

	if (m_iDirection == 0)
	{
		m_iDirection = -1;
	}
}

CMotherShip::~CMotherShip()
{

}

bool
CMotherShip::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

	return (true);
}

void
CMotherShip::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CMotherShip::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		Movement();

		//_fTime = clock->GetCurTime();

		CEntity::Process(_fDeltaTick);
	}
}

void
CMotherShip::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CMotherShip::IsHit() const
{
	return (m_bHit);
}

void CMotherShip::Movement()
{
	m_fX += 0.2 * m_iDirection;

}


