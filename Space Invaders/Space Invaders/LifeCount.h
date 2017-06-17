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

#if !defined(__LIFECOUNT_H__)
#define __LIFECOUNT_H__

// Library Includes

// Local Includes
#include "entity.h"

class CLifeCount : public CEntity
{
public:
	CLifeCount(const float _iX, const float _iY);
	~CLifeCount();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();
};
# endif

