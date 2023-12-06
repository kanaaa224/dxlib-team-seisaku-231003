//////////////////////////////////////////////////
// ロード シーン
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

LoadScene::LoadScene() {
	state        = 0;
	frameCounter = 0;

	progress = 0.0f;
	opacity  = 0.0f;

	//////////////////////////////////////////////////

	if ((img_background = LoadGraph("./resources/images/background.png")) == -1) throw;
	if ((img_cat = LoadGraph("./resources/images/animal_chara_computer_neko.png")) == -1) throw;
};

LoadScene::~LoadScene() {
	DeleteGraph(img_background);
	DeleteGraph(img_cat);
};

Scene* LoadScene::update() {
	if ((int)FPSCtrl::Get()) {
		frameCounter++;

		switch (state) {
		case 0:
			//float addition = 0.02f;
			//addition *= (FPSCtrl::Get() / 60.0f);
			opacity += 0.02f;
			if (opacity >= 1.0f) state = 1;

			break;

		case 1:
			if (frameCounter % ((int)FPSCtrl::Get() * 4) == 0) state = 2;
			progress += 0.01f; // 仮（配列でアニメーションさせる予定）
			break;

		case 2:
			//addition = 0.02f;
			//addition *= (FPSCtrl::Get() / 60.0f);
			opacity -= 0.02f;
			if (opacity <= 0.0f) return new GameScene();

			break;
		};
	};

	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene();
	if (InputCtrl::GetKeyState(KEY_INPUT_S))      return new GameScene();

	return this;
};

void LoadScene::draw() const {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * opacity);

	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img_background, TRUE);
	DrawRotaGraph(620, 470, 0.5, 0.0, img_cat, true);

	SetFontSize(40);
	std::string str = "ロード中...(仮)";
		DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(str.c_str()) / 2, 300, 0xffffff, str.c_str());
	SetFontSize(20);
	str = "Sキーでスキップ";
	DrawFormatString((SCREEN_WIDTH / 2) - GetDrawFormatStringWidth(str.c_str()) / 2, 340, 0xffffff, str.c_str());

	DrawBox(0, SCREEN_HEIGHT - 70, SCREEN_WIDTH * progress, SCREEN_HEIGHT, GetColor(255, 255, 255), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};