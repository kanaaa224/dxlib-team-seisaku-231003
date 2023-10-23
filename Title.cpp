#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "sourceFiles/inputCtrl.h"

//コンストラクタ
Title::Title()
{
	EnemyImage0 = LoadGraph("resources/images/(仮)魔法使い.png");
	EnemyImage1 = LoadGraph("resources/images/(仮)スケルトン.png");
	EnemyImage2 = LoadGraph("resources/images/(仮)スライム.png");
	EnemyImage3 = LoadGraph("resources/images/(仮)ミノタウロス.png");
	EnemyImage4 = LoadGraph("resources/images/(仮)まおう.png");
}

//デストラクタ
Title::~Title()
{

}

//更新
Scene*Title::update()
{
	InputCtrl::Update();
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		return new GameMain;
	}
	return this;
}

//描画
void Title::draw() const
{
	//DrawGraph(0, 0, EnemyImage0,FALSE);
	SetFontSize(75);
	DrawString(470, 300, "Start", 0xffffff);
	DrawString(470, 370, "Help", 0xffffff);
	DrawString(470, 440, "Credit", 0xffffff);
	DrawString(470, 510, "End", 0xffffff);
}