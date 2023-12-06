#pragma once

#include "scene.h"

#define END_PLAYER_ANIM_FPS 40
#define END_MOVE_UP 0.5f;
#define END_MOVE_DOWN -0.5f

class End :public Scene
{
private:
	int g_WaitTime;
	int EndImage;
	int End_Enemmy_Slime_Img[2];
	int End_Playercharacter_Img[3];
	int End_Thankyou_Text;
	int End_Enemmy_Img;
	int End_Player_Img;

	float End_Text__y;
	float End_Text_move_y;

	bool End_Text_location_y_flg;

	int End_fps;
	int End_Slime_fps;

	int End_Debug_Mouse_x;
	int End_Debug_Mouse_y;

public:
	End();
	~End();
	Scene* update()override;
	void draw()const override;

	void End_Thankyou_Text_Anim();

	void End_Playercharacter_Anim();
	void End_Slime_Anim();

};

