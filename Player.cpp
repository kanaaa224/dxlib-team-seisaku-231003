#include "main.h"
#include "Player.h"

Player::Player() {

	if (PlayerImg = LoadGraph("resources/images/yusya_red.png")) {}

	PlayerX = 640;
	PlayerY = 360;

	Provisional_LStickX = 0.0;
	Provisional_LStickY = 0.0;
}

Player::~Player() {

	DeleteGraph(PlayerImg);
}

void Player::update() {

	Provisional_LStickX = InputCtrl::GetStickRatio(R).x;
	Provisional_LStickY = InputCtrl::GetStickRatio(R).y;

}

void Player::draw()const {

	DrawFormatString(0, 300, GetColor(255, 255, 255), "LStick:ècé≤íl %0.1f", Provisional_LStickY);
	DrawFormatString(0, 320, GetColor(255, 255, 255), "LStick:â°é≤íl %0.1f", Provisional_LStickX);

	//DrawGraph(0, 300, PlayerImg, TRUE);

	DrawRotaGraph(PlayerX, PlayerY, 0.10f, 0.01, PlayerImg, TRUE);
}

int Player::Player_LStickY() {

	return Provisional_LStickY;

}

int Player::Player_LStickX() {

	return Provisional_LStickX;

}
