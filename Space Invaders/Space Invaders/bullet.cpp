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

// This Includes
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBullet::CBullet()
: m_fVelocityY(0.0f)
{

}

CBullet::~CBullet()
{

}

bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
    VALIDATE(CEntity::Initialise(IDB_BALLSPRITE, IDB_BALLMASK));
    
    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityY = _fVelocityY;

    return (true);
}

void
CBullet::Draw()
{
    CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick)
{
    //m_fX += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    CEntity::Process(_fDeltaTick);
}

float 
CBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

float 
CBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
