#include "main.h"
#include "Stage.h"

Stage::Stage() {

	if (StageImg1 = LoadGraph("resources/images/stageimage2.png")) {}
	/*if (StageImg2 = LoadGraph("resources/images/stageimage2.png")) {}
	if (StageImg3 = LoadGraph("resources/images/stageimage2.png")) {}
	if (StageImg4 = LoadGraph("resources/images/stageimage2.png")) {}*/

	for (int i = 0; i < 4; i++) {

		StageArrayImg[i].img = LoadGraph("resources/images/stageimage2.png");
		StageArrayImg[i].x = 0.0;
		StageArrayImg[i].y = 0.0;

	}



	/*StageX = 640.0;
	StageY = 369.5;*/

	Provisional_RStickX = 0;
	Provisional_RStickY = 0;

	Xspeed = 2.0;
	Yspeed = 2.0;
}

Stage::~Stage() {

	DeleteGraph(StageImg1);
	/*DeleteGraph(StageImg2);
	DeleteGraph(StageImg3);
	DeleteGraph(StageImg4);*/

}

void Stage::update() {

	Provisional_RStickX = InputCtrl::GetStickRatio(L).x;
	Provisional_RStickY = InputCtrl::GetStickRatio(L).y;

	//‰¡
	if (Provisional_RStickX > MOVE_RIGHT) {

		//StageX = StageX + Xspeed;
		for (int i = 0; i < 4; i++) {
			StageArrayImg[i].x = StageArrayImg[i].x - Xspeed;
		}
	}
	else if (Provisional_RStickX < MOVE_LEFT) {

		//StageX = StageX - Xspeed;
		for (int i = 0; i < 4; i++) {
			StageArrayImg[i].x = StageArrayImg[i].x + Xspeed;
		}
	}

	//c
	if (Provisional_RStickY > MOVE_UP) {

		//StageY = StageY - Yspeed;
		for (int i = 0; i < 4; i++) {
			StageArrayImg[i].y = StageArrayImg[i].y + Yspeed;
		}
	}
	else if (Provisional_RStickY < MOVE_DOWN) {

		//StageY = StageY + Yspeed;
		for (int i = 0; i < 4; i++) {
			StageArrayImg[i].y = StageArrayImg[i].y - Yspeed;
		}
	}

}

void Stage::draw()const {

	DrawFormatString(0, 340, GetColor(255, 255, 255), "RStick:cŽ²’l %0.1f", Provisional_RStickX);
	DrawFormatString(0, 360, GetColor(255, 255, 255), "RStick:‰¡Ž²’l %0.1f", Provisional_RStickY);

	//DrawGraph(StageX, StageY, StageImg1, TRUE);

	//¶ã
	DrawGraph(StageArrayImg[0].x + STAGEIMG_X, StageArrayImg[0].y + STAGEIMG_Y, StageArrayImg[0].img, TRUE);

	//‰Eã
	DrawGraph(StageArrayImg[1].x, StageArrayImg[1].y + STAGEIMG_Y, StageArrayImg[1].img, TRUE);

	//¶‰º
	DrawGraph(StageArrayImg[2].x + STAGEIMG_X, StageArrayImg[2].y, StageArrayImg[2].img, TRUE);

	//‰E‰º
	DrawGraph(StageArrayImg[3].x, StageArrayImg[3].y, StageArrayImg[3].img, TRUE);

	//DrawRotaGraph(StageX, StageY, 1.0f, 1, StageImg, TRUE);
}