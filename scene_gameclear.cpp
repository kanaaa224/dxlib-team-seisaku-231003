#include "scene_gameclear.h"
#include "scene_gameover.h"			// 仮

GameClearScene::GameClearScene()
{
	// 画像読込
	img_gameclear = LoadGraph("resources/images/gameclear.png");
	img_button_a = LoadGraph("resources/images/button_a.png");
}

GameClearScene::~GameClearScene()
{

}

Scene* GameClearScene::update()
{
#ifdef _DEBUG
	// スペースキーでゲームオーバー画面へ
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS) {
		return new GameOverScene;
	}
#endif

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		return new ResultScene;
	}

	return this;
}

void GameClearScene::draw() const
{
	// 背景色
	//DrawBox(0, 0, 1280, 720, 0xFFFFB5, TRUE);

	// 画像表示
	DrawGraph(0, 0, img_gameclear, TRUE);
	DrawGraph(1100, 670, img_button_a, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(545, 515, 0xffffff, "GAME CLEAR");
	SetFontSize(20);
	DrawFormatString(1150, 680, 0xffffff, "RESULT");

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif
}
