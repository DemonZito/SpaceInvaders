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

#if !defined(__PLAYER_H__)
#define __PLAYER_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "bullet.h"

// Types

// Constants

// Prototypes
class CPlayer : public CEntity
{
    // Member Functions
public:
    CPlayer();
    virtual ~CPlayer();

    virtual bool Initialise(const int _iScreenWidth);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	CBullet* GetBullet();
	void SetBullet(CBullet*);

	void SetHit(bool _b);
	bool IsHit() const;

	void LoseLife();
	int GetLives();

	void SetBulletSpeed(float _iBulletSpeed);

protected:

private:
    CPlayer(const CPlayer& _kr);
    CPlayer& operator= (const CPlayer& _kr);
	int m_iScreenWidth;

    // Member Variables
public:

protected:
	bool m_bHit;

private:
	CBullet* m_pBullet = nullptr;
	int m_iHealth;
	float m_iBulletSpeed;

};

#endif    // __PADDLE_H__
