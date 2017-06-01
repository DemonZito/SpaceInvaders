#pragma once
#include "enemy.h"

class CBigInvader : public IEnemy
{
public:

	bool Initialise();
	int GetPoints();
};

