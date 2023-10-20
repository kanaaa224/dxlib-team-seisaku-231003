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

public:
	Title();
	~Title();
	virtual Scene* Update() = 0;
	virtual void draw() const = 0;

};