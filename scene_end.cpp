#include "main.h"

End::End()
{
	if (EndImage = LoadGraph("resources/images/End/End_background_Img.png")) {}
	if (End_Thankyou_Text = LoadGraph("resources/images/End/logo_Thank_you_for_playing.png")) {}
	if (End_Enemmy_Slime_Img[0] = LoadGraph("resources/images/End/slime03_blue01_9.png")) {}
	if (End_Enemmy_Slime_Img[1] = LoadGraph("resources/images/End/slime03_blue01_10.png")) {}
	if (End_Playercharacter_Img[0] = LoadGraph("resources/images/player_images/Player_right50・50.png")) {}
	if (End_Playercharacter_Img[1] = LoadGraph("resources/images/player_images/Player_right_move1鎧150.50.png")) {}
	if (End_Playercharacter_Img[2] = LoadGraph("resources/images/player_images/Player_right_move2鎧250.50.png")) {}

	End_Enemmy_Img = 0;

	g_WaitTime = 0;
	End_Text__y = -50.0f;
	End_Text_move_y = 0.0;
	End_Text_location_y_flg = false;

	End_fps = 0;
	End_Slime_fps = 0;
}

End::~End()
{
	DeleteGraph(EndImage);
	DeleteGraph(End_Thankyou_Text);

	for (int i = 0; i < 2; i++) {

		DeleteGraph(End_Enemmy_Slime_Img[i]);
	}

	for (int i = 0; i < 3; i++) {

		DeleteGraph(End_Playercharacter_Img[i]);
	}
}

Scene* End::update()
{
	End_fps++;
	End_Slime_fps++;

	End_Debug_Mouse_x = InputCtrl::GetMouseCursor().x;
	End_Debug_Mouse_y = InputCtrl::GetMouseCursor().y;

	if (++g_WaitTime > 360)
	{
		return nullptr;
	}

	End_Thankyou_Text_Anim();
	End_Text__y = End_Text__y + End_Text_move_y;

	End_Playercharacter_Anim();
	End_Slime_Anim();

	if (End_fps > 59) {
		End_fps = 0;
	}

	if (End_Slime_fps >= 120) {
		End_Slime_fps = 0;
	}

	return this;
}

void End::draw()const
{
	DrawGraph(0, 0, EndImage, TRUE);
	
	//デバッグ用マウス座標
	/*DrawFormatString(0, 300, GetColor(255, 0, 0), "Mouse x %d", End_Debug_Mouse_x);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "Mouse y %d", End_Debug_Mouse_y);
	DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);*/

	DrawRotaGraph(630, End_Text__y, 0.5, 0.0, End_Thankyou_Text, TRUE);

	DrawRotaGraph(880, 580, 4.0, 0.0, End_Player_Img, TRUE);
	DrawRotaGraph2(300, 480, 0, 0, 0.6, 0.0, End_Enemmy_Img, TRUE, TRUE);
}

void End::End_Thankyou_Text_Anim() {

	if (End_Text__y < /*75*/ 100 && End_Text_location_y_flg == true) {
		End_Text_move_y = 0.0f;
	}
	else {

		if (End_Text__y > 150.0f) {

			End_Text_location_y_flg = true;
			End_Text_move_y = End_Text_move_y + TITLE_MOVE_DOWN;
		}
		else {

			End_Text_move_y = End_Text_move_y + TITLE_MOVE_UP;
		}
	}
}

void End::End_Playercharacter_Anim() {

	if (End_fps % END_PLAYER_ANIM_FPS >= 0 && End_fps % END_PLAYER_ANIM_FPS < 11) {
		End_Player_Img = End_Playercharacter_Img[0];
	}
	else if (End_fps % END_PLAYER_ANIM_FPS > 10 && End_fps % END_PLAYER_ANIM_FPS < 21) {
		End_Player_Img = End_Playercharacter_Img[1];
	}
	else if (End_fps % END_PLAYER_ANIM_FPS > 20 && End_fps % END_PLAYER_ANIM_FPS < 31) {
		End_Player_Img = End_Playercharacter_Img[0];
	}
	else if (End_fps % END_PLAYER_ANIM_FPS > 30 && End_fps % END_PLAYER_ANIM_FPS < 40) {
		End_Player_Img = End_Playercharacter_Img[2];
	}
}

void End::End_Slime_Anim() {

	if (End_Slime_fps >= 1 && End_Slime_fps <= 60) {
		End_Enemmy_Img = End_Enemmy_Slime_Img[0];
	}
	else if (End_Slime_fps >= 61 && End_Slime_fps <= 120) {
		End_Enemmy_Img = End_Enemmy_Slime_Img[1];
	}
}