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

// Local Includes
#include "entity.h"

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

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void SetHit(bool _b);
    bool IsHit() const;

protected:

private:
    IEnemy(const IEnemy& _kr);
    IEnemy& operator= (const IEnemy& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;

private:

};


#endif    // __BRICK_H__

