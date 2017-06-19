//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: EnemyBullet.h
// Description	: Header file for the enemies, all invaders inherit off this
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__ENEMYBULLET_H__)
#define __ENEMYBULLET_H__

// Library Includes

// Local Includes
//#include "entity.h"
#include "bullet.h"

// Types

// Constants

// Prototypes
class CSprite;

class CEnemyBullet : public CBullet
{
	// Member Functions
public:
	CEnemyBullet();
	virtual ~CEnemyBullet();

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY, float _fDeltaTick);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	float GetVelocityY() const;
	void SetVelocityY(float _fY);

	float GetRadius() const;

protected:

private:

	CEnemyBullet(const CEnemyBullet& _kr);
	CEnemyBullet& operator= (const CEnemyBullet& _kr);

	// Member Variables
public:

protected:
	float m_fVelocityY;

private:

};


#endif    // __BALL_H__
