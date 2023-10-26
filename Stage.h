#pragma once

#define STAGEIMG_X 640.0f
#define STAGEIMG_Y 369.5f

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

	int Provisional_RStickX;
	int Provisional_RStickY;

	float Xspeed;
	float Yspeed;

public:
	Stage();
	~Stage();

	void update();

	//•`‰æˆ—
	void draw() const;


};