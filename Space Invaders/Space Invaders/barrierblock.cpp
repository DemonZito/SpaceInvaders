//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: barrierblock.cpp
// Description	: The protection blocks
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "barrierblock.h"



CBarrierBlock::CBarrierBlock(const float _iX, const float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


CBarrierBlock::~CBarrierBlock()
{
}

bool
CBarrierBlock::Initialise(float _fDeltaTick)
{
	VALIDATE(CEntity::Initialise(IDB_BARRIERBLOCK, IDB_BARRIERBLOCKMASK));
	CEntity::m_pSprite->SetDestSizeW(25);
	CEntity::m_pSprite->SetDestSizeH(25);
	CEntity::Process(_fDeltaTick);
	return (true);
}

void
CBarrierBlock::Draw()
{
	CEntity::Draw();
}
