#pragma once

class Stage {

private:
	int StageX;
	int StageY;
	int StageImg;

public:
	Stage();
	~Stage();

	void update(GameScene* gameScene);

	//•`‰æˆ—
	void draw() const;


};