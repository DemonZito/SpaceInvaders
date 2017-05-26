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

// This Include
#include "enemy.h"

// Static Variables

// Static Function Prototypes

// Implementation

IEnemy::IEnemy()
	: m_bHit(false),
	m_fTime(0),
	m_iSpeed(10),
	m_iDirection(1),
	m_bWallHit(false)
{
	
}

IEnemy::~IEnemy()
{

}

bool
IEnemy::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void
IEnemy::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
IEnemy::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
		Movement(_fDeltaTick);

		//_fTime = clock->GetCurTime();

        CEntity::Process(_fDeltaTick);
    }
}

void
IEnemy::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
IEnemy::IsHit() const
{
    return (m_bHit);
}

void IEnemy::shoot() {
	m_pBullet = new CBullet();
	m_pBullet->Initialise(m_fX, m_fY + 15, 260.0);
}

void IEnemy::Movement(float _fDeltaTick)
{
	m_fTime += _fDeltaTick;

	if (m_fTime >= 1.0)
	{
		if (m_bWallHit == true)
		{
			m_fY += 20;
			m_fTime = 0;
			m_bWallHit = false;
		}
		else
		{
			m_fX += m_iSpeed * m_iDirection;
			m_fTime = 0;
		}
		
	}
	
}

CBullet * IEnemy::GetBullet()
{
	return m_pBullet;
}

void IEnemy::SetBullet(CBullet * _pBullet)
{
	m_pBullet = _pBullet;
}


