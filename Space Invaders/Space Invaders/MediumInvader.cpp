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
	const int iMask = IDB_BITMAP3;

	int iSprite = IDB_BITMAP2;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(25);
	m_pAnim->SetSpeed(1.0f);
	m_pAnim->AddFrame(50);
	m_pAnim->AddFrame(75);
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