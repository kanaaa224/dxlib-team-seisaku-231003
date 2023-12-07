#include "DrawHelp.h"
#include "DxLib.h"
#include "main.h"

//DrawHelp::DrawHelp()
//{
//	//ヘルプ2画像の読込
//	HelpImage2 = LoadGraph("resources/images/Help/Help2.png");
//}
//
//Scene* DrawHelp::update()
//{
//	//Aボタンでゲームメインへ遷移
//	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
//	{
//		SoundManager::StopSoundBGMs();
//		return new GameScene;
//	}
//	//Bボタンでタイトルへ遷移
//	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
//	{
//		return new Title;
//	}
//	return this;
//}
//
//void DrawHelp::draw() const
//{
//	//ヘルプ2画面の表示
//	DrawGraph(0, 0, HelpImage2, TRUE);
//	SetFontSize(40);
//	DrawString(520, 670, "Aボタン：スタート", 0xff0000);
//	DrawString(900, 670, "Bボタン：タイトル", 0xff0000);
//}
