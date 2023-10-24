//////////////////////////////////////////////////
// ロード シーン
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

Scene* LoadScene::update() {
	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene();

	return this;
};

void LoadScene::draw() const {
	SetFontSize(16);

	int x = 20,
		y = 50;

	//////////////////////////////////////////////////

	DrawFormatString(x, y, 0xffffff, "ロード画面");
};