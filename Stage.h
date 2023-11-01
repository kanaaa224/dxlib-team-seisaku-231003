#pragma once

#define STAGEIMG_X 640.0f*2
#define STAGEIMG_Y 369.5f*2

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

	StageArray StageArrayImg[4];

	float Xspeed;
	float Yspeed;

public:
	Stage();
	~Stage();

	void update(float moveX, float moveY);

	//•`‰æˆ—
	void draw() const;

	StageArray GetStageArray(int arrayNum)
	{
		return StageArrayImg[arrayNum];
	}
};