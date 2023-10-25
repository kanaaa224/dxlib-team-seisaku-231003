#include "scene_result.h"

ResultScene::ResultScene()
{
	img_button_a = LoadGraph("resources/images/button_a.png");
	//img = LoadGraph("resources/images/slime_cat.png");
}

ResultScene::~ResultScene()
{
}

Scene* ResultScene::update()
{
	// タイトルへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		//return new Title;
	}

	return this;
}

void ResultScene::draw() const
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Result");
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		DrawFormatString(0, 0, 0xffffff, "押されました");
	}
#endif

	// 画像表示
	DrawGraph(1000, 600, img_button_a, TRUE);

	// テキスト表示
	DrawFormatString(1150, 680, 0xffffff, "A:タイトル");

	DrawFormatString(10, 50, 0xffffff, "縮小マップ");

	DrawFormatString(700, 200, 0xffffff, "武器UI１");
	DrawFormatString(850, 150, 0xffffff, "武器名１");
	DrawFormatString(850, 200, 0xffffff, "Lv.              0");
	DrawFormatString(850, 250, 0xffffff, "総ダメージ数      100000");

	DrawFormatString(700, 450, 0xffffff, "武器UI２");
	DrawFormatString(850, 400, 0xffffff, "武器名２");
	DrawFormatString(850, 450, 0xffffff, "Lv.              0");
	DrawFormatString(850, 500, 0xffffff, "総ダメージ数      100000");

}
