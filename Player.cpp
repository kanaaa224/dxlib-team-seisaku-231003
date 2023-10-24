#include "main.h"
#include "Player.h"

Player::Player() {

	if (PlayerImg = LoadGraph("resources/images/yusya_red.png")) {}

	PlayerX = 640;
	PlayerY = 360;
}

Player::~Player() {

	DeleteGraph(PlayerImg);
}

void Player::update(GameScene* gameScene) {



}

void Player::draw()const {

	//DrawGraph(PlayerX, PlayerY, PlayerImg, TRUE);

	DrawRotaGraph(PlayerX, PlayerY, 0.10f, 0.01, PlayerImg, TRUE);
}