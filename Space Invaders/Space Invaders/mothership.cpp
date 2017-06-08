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

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "mothership.h"

// Static Variables

// Static Function Prototypes

// Implementation


bool
CMotherShip::Initialise()
{
	const int iMask = IDB_BITMAP3;

	int iSprite = IDB_BITMAP2;


	m_pAnim = new CAnimatedSprite();
	m_pAnim->Initialise(iSprite, iMask);
	m_pAnim->SetWidth(25);
	m_pAnim->SetSpeed(1.0f);
	m_pAnim->AddFrame(150);
	m_pAnim->AddFrame(175);
	m_pAnim->AddFrame(200);
	m_pAnim->AddFrame(225);
	m_pAnim->AddFrame(250);
	m_pAnim->AddFrame(275);
	m_pAnim->AddFrame(300);
	m_pAnim->AddFrame(325);
	m_pAnim->AddFrame(350);
	m_pAnim->AddFrame(375);
	m_pAnim->AddFrame(400);
	m_pAnim->AddFrame(425);
	m_pAnim->AddFrame(450);
	m_pAnim->AddFrame(475);
	m_pAnim->AddFrame(500);
	m_pAnim->AddFrame(525);
	m_pAnim->AddFrame(550);
	//m_pAnim->AddFrame(575);

	return (true);

	//return (true);
}

void
CMotherShip::Draw()
{
	m_pAnim->DrawAnimated();
}

void CMotherShip::Movement(float _fDeltaTick)
{
	m_fX += 0.2 * m_iDirection;

}


