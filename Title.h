#pragma once
#include "sourceFiles/scene.h"

class Title :public Scene
{
private:
	int TitleImage;

	enum class TITLE_MENU {
		START,
		HELP,
		CLEDIT,
		END
	};

	int EnemyImage0;
	int EnemyImage1;
	int EnemyImage2;
	int EnemyImage3;
	int EnemyImage4;

public:
	Title();
	~Title();
	Scene* update() override;
	void draw() const override;

};