#include "main.h"
#include "Stage.h"

Stage::Stage() {

	if (StageImg = LoadGraph("resources/images/stageimage2.png")) {}

	StageX = 0;
	StageY = 0;
}

Stage::~Stage() {

	DeleteGraph(StageImg);

}

void Stage::update(GameScene* gameScene) {



}

void Stage::draw()const {

	DrawGraph(StageX, StageY, StageImg, TRUE);

	//DrawRotaGraph(StageX, StageY, 1.0f, 1, StageImg, TRUE);
}