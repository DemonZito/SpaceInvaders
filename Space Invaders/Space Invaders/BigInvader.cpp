//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: BigInvader.cpp
// Description	: The largest alien type. Holds its sprite and points value
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//


// Library Includes
#include <vector>
// Local Includes
#include "resource.h"
#include "utils.h"
#include "AnimatedSprite.h"

// This Include
#include "BigInvader.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation


CBigInvader::~CBigInvader()
{

}

bool CBigInvader::Initialise()
{
	const int iMask = IDB_ENEMYMASK;

	int iSprite = IDB_ENEMIES;

	//VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	//m_pAnim->Initialise(IDB_SMALLINVADER, IDB_BRICKMASK);
	m_pAnim->SetWidth(25);
	m_pAnim->SetSpeed(1.0f);
	m_pAnim->AddFrame(0);
	m_pAnim->AddFrame(25);

	CEntity::m_pAnim->SetDestSizeW(50);
	CEntity::m_pAnim->SetDestSizeH(50);

	return (true);
}

int CBigInvader::GetPoints()
{
	return 10;
}

void CBigInvader::Draw()
{
	m_pAnim->DrawAnimated();
}

