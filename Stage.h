#pragma once

#define STAGEIMG_X 1275
#define STAGEIMG_Y 703

struct StageArray {
	float x;
	float y;
	int img;
};

class Stage {

private:
	float StageX;
	float StageY;

	int	StageImg1;
	int	StageImg2;
	int	StageImg3;
	int	StageImg4;

	StageArray StageArrayImg[9];

	float Xspeed;
	float Yspeed;

public:
	Stage();
	~Stage();

	void update(float moveX, float moveY);

	//•`‰æˆ—
	void draw() const;

	void init();

	StageArray GetStageArray(int arrayNum)
	{
		return StageArrayImg[arrayNum];
	}
};