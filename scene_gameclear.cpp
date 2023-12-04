#include "main.h"

GameClearScene::GameClearScene()
{
	// 画像読込
	img_gameclear = LoadGraph("resources/images/gameclear.png");
	img_button_a = LoadGraph("resources/images/button_a01.png");

	SoundManager::SetBGM("bgm_gameclear");
	SoundManager::SetVolumeBGM("bgm_gameclear", 50);
}

GameClearScene::~GameClearScene()
{

}

Scene* GameClearScene::update()
{
	SoundManager::PlaySoundBGM("bgm_gameclear");

	// スペースキーでゲームオーバー画面へ
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS) {
		//return new GameOverScene();
	}

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		//return new ResultScene;
	}

	return this;
}

void GameClearScene::draw() const
{
	// 背景色
	//DrawBox(0, 0, 1280, 720, 0xFFFFB5, TRUE);

	// 画像表示
	DrawGraph(0, 0, img_gameclear, TRUE);
	DrawRotaGraph(1150, 690, 0.2f, 0.0f, img_button_a, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(545, 515, 0xffffff, "GAME CLEAR");
	SetFontSize(20);
	DrawFormatString(1175, 680, 0xffffff, "RESULT");

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif
}
