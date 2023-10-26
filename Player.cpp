#include "main.h"
#include "Player.h"

Player::Player() {

	if (PlayerImg = LoadGraph("resources/images/yusya_red.png")) {}
	if (AimingImg = LoadGraph("resources/images/Syoujun_kari.png")) {}

	PlayerX = 640;
	PlayerY = 360;

	AimingX = 300.0;
	AimingY = 300.0;

	Provisional_LStickX = 0.0;
	Provisional_LStickY = 0.0;

	Additional_Value = 10.0;
}

Player::~Player() {

	DeleteGraph(PlayerImg);
	DeleteGraph(AimingImg);
}

void Player::update() {

	Provisional_LStickX = InputCtrl::GetStickRatio(R).x;
	Provisional_LStickY = InputCtrl::GetStickRatio(R).y;



	//‰¡
	if (Provisional_LStickX > MOVE_RIGHT) {

		AimingX = AimingX + Additional_Value * Provisional_LStickX;
	}
	else if (Provisional_LStickX < MOVE_LEFT) {

		AimingX = AimingX + Additional_Value * Provisional_LStickX;
	}

	//c
	if (Provisional_LStickY > MOVE_UP) {

		AimingY = AimingY - Additional_Value * Provisional_LStickY;
	}
	else if (Provisional_LStickY < MOVE_DOWN) {

		AimingY = AimingY - Additional_Value * Provisional_LStickY;

	}
}

void Player::draw()const {

	DrawFormatString(0, 300, GetColor(255, 255, 255), "LStick:cŽ²’l %0.1f", Provisional_LStickY);
	DrawFormatString(0, 320, GetColor(255, 255, 255), "LStick:‰¡Ž²’l %0.1f", Provisional_LStickX);

	//DrawGraph(0, 300, PlayerImg, TRUE);

	DrawRotaGraph(AimingX, AimingY, 0.10f, 0.01, AimingImg, TRUE);

	DrawRotaGraph(PlayerX, PlayerY, 0.10f, 0.01, PlayerImg, TRUE);
}

int Player::Player_AimingX() {

	return AimingX;

}

int Player::Player_AimingY() {

	return AimingY;

}
