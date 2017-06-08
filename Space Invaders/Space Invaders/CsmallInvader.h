#pragma once
#include "enemy.h"

class CSmallInvader : public IEnemy
{
public:
	~CSmallInvader();
	bool Initialise();
	int GetPoints();
	void Draw();
};

