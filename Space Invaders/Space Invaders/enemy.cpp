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
#include "enemy.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

IEnemy::IEnemy()
	: m_bHit(false),
	m_fTime(0),
	m_fSpeed(1.0f),
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

void IEnemy::shoot(std::vector<CEnemyBullet*> *_vecEnemyBullets)
{
	m_vecBullet.push_back(new CEnemyBullet());
	m_vecBullet.back()->Initialise(m_fX, m_fY + 15, 260.0);
	_vecEnemyBullets->push_back(m_vecBullet.back());
}

void IEnemy::Movement(float _fDeltaTick)
{
	m_fTime += _fDeltaTick;

	if (m_fTime >= m_fSpeed)
	{
		m_fX += 10 * m_iDirection;
		m_fTime = 0;
	}

}

void IEnemy::MoveDown(float _fDeltaTick)
{
	if (!m_bHit)
	{
		m_fY += 20;
		CEntity::Process(_fDeltaTick);
	}
}

CEnemyBullet * IEnemy::GetBullet()
{
	return m_vecBullet.back();
}

void IEnemy::SetBullet(CEnemyBullet * _pBullet)
{
	m_vecBullet.push_back(_pBullet);
}


