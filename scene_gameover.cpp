#include "scene_gameover.h"

GameOverScene::GameOverScene()
{
	img_gameover = LoadGraph("resources/images/gameover.png");
	img_button_a = LoadGraph("resources/images/button_a.png");

}

GameOverScene::~GameOverScene()
{

}

Scene* GameOverScene::update()
{
#ifdef _DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS) {
		return new ResultScene;
	}
#endif

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		return new ResultScene;
	}

	return this;
}

void GameOverScene::draw() const
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "GameOver");
#endif

	// 画像表示
	DrawGraph(0, 0, img_gameover, TRUE);
	DrawGraph(1000, 600, img_button_a, TRUE);

	DrawFormatString(0, 70, 0xffffff, "リザルト");

}
