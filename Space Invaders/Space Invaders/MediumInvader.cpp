//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: MediumInvader.cpp
// Description	: The medium alien type. Holds its sprite and points value
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes
#include <vector>
// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "MediumInvader.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation


CMediumInvader::~CMediumInvader()
{
	/*if (m_pAnim != nullptr)
	{
		delete m_pAnim;
		m_pAnim = 0;
	}*/
}

bool
CMediumInvader::Initialise()
{
	const int iMask = IDB_ENEMYMASK;

	int iSprite = IDB_ENEMIES;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(25);
	m_pAnim->SetSpeed(1.0f);
	m_pAnim->AddFrame(50);
	m_pAnim->AddFrame(75);

	CEntity::m_pAnim->SetDestSizeW(50);
	CEntity::m_pAnim->SetDestSizeH(50);

	return (true);
}

int CMediumInvader::GetPoints()
{
	return 30;
}

void CMediumInvader::Draw()
{
	m_pAnim->DrawAnimated();
}