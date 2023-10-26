#include "scene_gameover.h"
#include "scene_gameclear.h"		// 仮

GameOverScene::GameOverScene()
{
	// 画像読込
	img_gameover = LoadGraph("resources/images/gameover.png");
	img_ghost = LoadGraph("resources/images/ghost.png");
	img_button_a = LoadGraph("resources/images/button_a.png");

	// 変数の初期化
	ghost_x = 750;
	ghost_y = 150;
	count = 0;

	value = 255;
}

GameOverScene::~GameOverScene()
{

}

Scene* GameOverScene::update()
{
#ifdef _DEBUG
	// スペースキーでゲームクリア画面へ
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS) {
		return new GameClearScene;
	}
#endif

	if (value > 0)
	{
		value--;
	}
	else
	{
		value = 0;
	}

	if (count < FPS_PERIOD)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		return new ResultScene;
	}

	return this;
}

void GameOverScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);

	// 画像表示
	DrawGraph(0, 0, img_gameover, TRUE);
	// sin( PI*2 / 周期 * Count ) * 振幅
	DrawGraph(ghost_x, ghost_y + sinf(M_PI * 2 / FPS_PERIOD * count) * 40, img_ghost, TRUE);
	DrawGraph(1100, 670, img_button_a, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(545, 515, 0x000000, "GAME OVER");
	SetFontSize(20);
	DrawFormatString(1150, 680, 0x000000, "RESULT");

	//フェードの設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

	//黒で塗りつぶし
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);

	//デフォルトに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


#ifdef _DEBUG
	//DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
	DrawFormatString(0, 0, 0xffffff, "%d",count);

#endif

}
