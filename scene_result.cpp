#include "scene_result.h"

ResultScene::ResultScene()
{
	// 画像読込
	img_button_a = LoadGraph("resources/images/button_a.png");

	// 変数の初期化
	value = 180;
}

ResultScene::~ResultScene()
{

}

Scene* ResultScene::update()
{
	// ブレンドモードのパラメータ
	if (value > 0)
	{
		value--;
	}
	else
	{
		value = 0;
	}

	// タイトルへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		return new Title;
	}

	return this;
}

void ResultScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);

	// 画像表示
	DrawGraph(1100, 670, img_button_a, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(550, 10, 0x000000, "RESULT");
	SetFontSize(20);
	DrawFormatString(1150, 680, 0x000000, "TITLE");

	DrawFormatString(10, 50, 0x000000, "縮小マップ");

	DrawFormatString(700, 200, 0x000000, "武器UI１");
	DrawFormatString(850, 150, 0x000000, "武器名１");
	DrawFormatString(850, 200, 0x000000, "Lv.              0");
	DrawFormatString(850, 250, 0x000000, "総ダメージ数      100000");

	DrawFormatString(700, 450, 0x000000, "武器UI２");
	DrawFormatString(850, 400, 0x000000, "武器名２");
	DrawFormatString(850, 450, 0x000000, "Lv.              0");
	DrawFormatString(850, 500, 0x000000, "総ダメージ数      100000");

	//フェードの設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

	//黒で塗りつぶし
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);

	//デフォルトに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif

}
