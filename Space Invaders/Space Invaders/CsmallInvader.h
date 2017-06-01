#pragma once
#include "enemy.h"

class CSmallInvader : public IEnemy
{
public:

	bool Initialise();
	int GetPoints();
};

