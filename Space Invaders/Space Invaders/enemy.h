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

#if !defined(__ENEMY_H__)
#define __ENEMY_H__

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

class IEnemy : public CEntity
{
	// Member Functions
public:
	IEnemy();
	virtual ~IEnemy();

	virtual bool Initialise();

	void Draw();
	void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;
	void shoot(std::vector<CEnemyBullet*> *_vecEnemyBullets);

	virtual void Movement(float _fDeltaTick);
	virtual int GetPoints();
	void SetSpeed(float _fSpeed);

protected:

private:
	IEnemy(const IEnemy& _kr);
	IEnemy& operator= (const IEnemy& _kr);

	// Member Variables
public:
	float m_fSpeed;
	int m_iDirection;
	bool m_bWallHit;

	void MoveDown(float _fDeltaTick);
	CEnemyBullet* GetBullet();
	void SetBullet(CEnemyBullet*);
protected:
	bool m_bHit;

private:
	float m_fTime;
	CClock* clock;
	//std::vector<CEnemyBullet*> m_vecBullet;
	CEnemyBullet* m_eneBullet;
	//int m_iPoints;

};


#endif    // __BRICK_H__

