#include "main.h"

Credit::Credit()
{
	//クレジット画像の読込
	CreditImage = LoadGraph("resources/images/Title/Title_background_tree tower_1280.png");
	//時間の初期化
	g_WaitTime = 0;
	g_PosY_D = 450;

	Credit_Mouse_x = 0;
	Credit_Mouse_y = 0;
}

Credit::~Credit()
{
	DeleteGraph(CreditImage);
}

Scene* Credit::update()
{
	//クレジットロール処理
	//時間がたてばタイトルへ遷移

	//デバッグ用 あとで消す
	//Credit_Mouse_x = InputCtrl::GetMouseCursor().x;
	//Credit_Mouse_y = InputCtrl::GetMouseCursor().y;

	

	if (++g_WaitTime < /*2370*/  2480) {

		//if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESSED) g_PosY_D -= 5;
		g_PosY = /*600*/ g_PosY_D - g_WaitTime;
	}
	else {

		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	//背景画像
	DrawGraph(0, 0, CreditImage, TRUE);

	//　中心線
	//DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	//DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//DrawFormatString(0, 300, GetColor(255, 0, 0), "%d", g_PosY, TRUE);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "%d", g_WaitTime, TRUE);

	//使ったサイトや関係者名の名前を表示
	SetFontSize(50);

	//DrawString(575, 350 + g_PosY, "BOOTH", 0xffffff);

	DrawString(535, 350 + g_PosY, "画像など", 0xffffff);
	DrawString(470, 450 + g_PosY, "PIXELART TOWN", 0xffffff);
	DrawString(560, 550 + g_PosY, "DOTOWN", 0xffffff);
	DrawString(520, 650 + g_PosY, "DOTILLUST", 0xffffff);
	DrawString(530, 750 + g_PosY, "illustAC", 0xffffff);
	DrawString(480, 850 + g_PosY, "UTILITY-LABO", 0xffffff);
	DrawString(480, 950 + g_PosY, "BANNERKOUBOU", 0xffffff);
	DrawString(460, 1050 + g_PosY, "Game-icons.net", 0xffffff);
	DrawString(485, 1150 + g_PosY, "いろいろ倉庫", 0xffffff);
	DrawString(575, 1250 + g_PosY, "BOOTH", 0xffffff);
	DrawString(250, 1350 + g_PosY, "グラフィックデザイン科のみなさん", 0xffffff);

	DrawString(500, 1550 + g_PosY, "SE・BGMなど", 0xffffff);	//+ 200
	DrawString(472, 1650 + g_PosY, "DOVA-SYNDROME", 0xffffff);
	DrawString(510, 1750 + g_PosY, "ユーフルカ", 0xffffff);
	DrawString(513, 1850 + g_PosY, "効果音工房", 0xffffff);
	DrawString(513, 1950 + g_PosY, "効果音ラボ", 0xffffff);

	//DrawString(410, 2150 + g_PosY, "スペシャルサンクス", 0xffffff);		//+ 200
	//DrawString(250, 2250 + g_PosY, "グラフィックデザイン科のみなさん", 0xffffff);
}
