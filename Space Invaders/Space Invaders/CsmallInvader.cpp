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
#include "CsmallInvader.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation


CSmallInvader::~CSmallInvader()
{
	/*if (m_pAnim != nullptr)
	{
		delete m_pAnim;
		m_pAnim = 0;
	}*/
}

bool
CSmallInvader::Initialise()
{
	const int iMask = IDB_ENEMYMASK;

	int iSprite = IDB_ENEMIES;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(25);
	m_pAnim->SetSpeed(1.0f);
	m_pAnim->AddFrame(100);
	m_pAnim->AddFrame(125);

	CEntity::m_pAnim->SetDestSizeW(50);
	CEntity::m_pAnim->SetDestSizeH(50);

	return (true);
}

int CSmallInvader::GetPoints()
{
	return 50;
}

void CSmallInvader::Draw()
{
	m_pAnim->DrawAnimated();
}
