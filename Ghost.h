#pragma once
#include "EnemyBase.h"

class Ghost :public EnemyBase
{
private:
	
public:
	Ghost(int arrayNum);
	~Ghost();
	void Update(Player* player);
	void Draw() const;

	int SetRespawnTimeGhost(int arrayNum);
	Location SetRespawnPostionGhost(int arrayNum);
};

