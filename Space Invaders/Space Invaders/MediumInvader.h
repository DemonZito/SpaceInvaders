#pragma once
#include "enemy.h"

class CMediumInvader : public IEnemy
{
public:

	bool Initialise();
	int GetPoints();
};

