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
#include "entity.h"
#include "clock.h"
#include "bullet.h"
#include "EnemyBullet.h"


// Types

// Constants

// Prototypes

class CMotherShip : public CEntity
{
	// Member Functions
public:
	CMotherShip(const int _iDirection = 1);
	virtual ~CMotherShip();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

	void Movement();

protected:

private:
	CMotherShip(const CMotherShip& _kr);
	CMotherShip& operator= (const CMotherShip& _kr);

	// Member Variables
public:
	float m_fSpeed;
	int m_iDirection;
	bool m_bWallHit;

protected:
	bool m_bHit;

private:
	float m_fTime;
	CClock* clock;

};


#endif    // __BRICK_H__

