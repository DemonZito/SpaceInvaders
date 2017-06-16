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

#if !defined(__BARRIERBLOCK_H__)
#define __BARRIERBLOCK_H__

// Library Includes

// Local Includes
#include "entity.h"
class CBarrierBlock : public CEntity
{
public:
	CBarrierBlock(const float _iX, const float _iY);
	~CBarrierBlock();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};

#endif    // __BARRIERBLOCK_H__

