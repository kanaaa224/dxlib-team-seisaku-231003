#include "main.h"
#include "Stage.h"
#include "Player.h"

Stage::Stage() {

	if (StageImg1 = LoadGraph("resources/images/stageimage2.png")) {}

	for (int i = 0; i < 4; i++) {

		StageArrayImg[i].img = LoadGraph("resources/images/stageimage2.png");
		StageArrayImg[i].x = 0.0;
		StageArrayImg[i].y = 0.0;

		switch (i)
		{
		case 0:
			break;
		case 1:
			StageArrayImg[i].x += STAGEIMG_X;
			break;
		case 2:
			StageArrayImg[i].y += STAGEIMG_Y;

			break;
		case 3:
			StageArrayImg[i].x += STAGEIMG_X;
			StageArrayImg[i].y += STAGEIMG_Y;
			break;
		default:
			break;
		}
	}



	/*StageX = 640.0;
	StageY = 369.5;*/

	Xspeed = 2.0;
	Yspeed = 2.0;
}

Stage::~Stage() {

	DeleteGraph(StageImg1);
}

void Stage::update() {

	//‰¡
	//if (Provisional_RStickX > MOVE_RIGHT) {

	//	//StageX = StageX + Xspeed;
	//	for (int i = 0; i < 4; i++) {
	//		StageArrayImg[i].x = StageArrayImg[i].x - Xspeed;
	//	}
	//}
	//else if (Provisional_RStickX < MOVE_LEFT) {

	//	//StageX = StageX - Xspeed;
	//	for (int i = 0; i < 4; i++) {
	//		StageArrayImg[i].x = StageArrayImg[i].x + Xspeed;
	//	}
	//}

	////c
	//if (Provisional_RStickY > MOVE_UP) {

	//	//StageY = StageY - Yspeed;
	//	for (int i = 0; i < 4; i++) {
	//		StageArrayImg[i].y = StageArrayImg[i].y + Yspeed;
	//	}
	//}
	//else if (Provisional_RStickY < MOVE_DOWN) {

	//	//StageY = StageY + Yspeed;
	//	for (int i = 0; i < 4; i++) {
	//		StageArrayImg[i].y = StageArrayImg[i].y - Yspeed;
	//	}
	//}

	//for (int i = 0; i < 4; i++) {
	//	StageArrayImg[i].x = Player::Player_MovingX();
	//	StageArrayImg[i].y = Player::Player_MovingY();
	//}

	StageArrayImg[0].x = Player::Player_MovingX();
	StageArrayImg[1].x = Player::Player_MovingX() + STAGEIMG_X;
	StageArrayImg[2].x = Player::Player_MovingX();
	StageArrayImg[3].x = Player::Player_MovingX() + STAGEIMG_X;

	StageArrayImg[0].y = Player::Player_MovingY();
	StageArrayImg[1].y = Player::Player_MovingY();
	StageArrayImg[2].y = Player::Player_MovingY() + STAGEIMG_Y;
	StageArrayImg[3].y = Player::Player_MovingY() + STAGEIMG_Y;

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			break;
		case 1:
			StageArrayImg[i].x += STAGEIMG_X;
			break;
		case 2:
			StageArrayImg[i].y += STAGEIMG_Y;

			break;
		case 3:
			StageArrayImg[i].x += STAGEIMG_X;
			StageArrayImg[i].y += STAGEIMG_Y;
			break;
		default:
			break;
		}
	}

}

void Stage::draw()const {

	//DrawGraph(StageX, StageY, StageImg1, TRUE);

	//¶ã
	DrawGraph(StageArrayImg[0].x /*+ STAGEIMG_X*/, StageArrayImg[0].y /*+ STAGEIMG_Y*/, StageArrayImg[0].img, TRUE);

	//‰Eã
	DrawGraph(StageArrayImg[1].x, StageArrayImg[1].y /*+ STAGEIMG_Y*/, StageArrayImg[1].img, TRUE);

	//¶‰º
	DrawGraph(StageArrayImg[2].x /*+ STAGEIMG_X*/, StageArrayImg[2].y, StageArrayImg[2].img, TRUE);

	//‰E‰º
	DrawGraph(StageArrayImg[3].x, StageArrayImg[3].y, StageArrayImg[3].img, TRUE);

	//DrawRotaGraph(StageX, StageY, 1.0f, 1, StageImg, TRUE);
}