#include "main.h"

Credit::Credit()
{
	//クレジット画像の読込
	CreditImage = LoadGraph("resources/images/Title/Title_background_tree.png");
	//時間の初期化
	g_WaitTime = 0;

	Credit_Mouse_x = 0;
	Credit_Mouse_y = 0;
}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	//クレジットロール処理
	//時間がたてばタイトルへ遷移

	//デバッグ用 あとで消す
	Credit_Mouse_x = InputCtrl::GetMouseCursor().x;
	Credit_Mouse_y = InputCtrl::GetMouseCursor().y;

	if (++g_WaitTime < /*1580*/ 2200) {

		g_PosY = /*600*/ 450 - g_WaitTime;
	}
	else {

		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	DrawGraph(0, 0, CreditImage, TRUE);

	DrawFormatString(0, 300, GetColor(255, 0, 0), "Mouse x %d", g_WaitTime);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "Mouse y %d", Credit_Mouse_y);

	//　中心線
	DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//使ったサイトや関係者名の名前を表示
	SetFontSize(50);
	DrawString(460, 350 + g_PosY, "使用したサイト", 0xffffff);
	DrawString(535, 450 + g_PosY, "画像など", 0xffffff);
	DrawString(470, 550 + g_PosY, "PIXELART TOWN", 0xffffff);
	DrawString(520, 650 + g_PosY, "DOTILLUST", 0xffffff);
	DrawString(530, 750 + g_PosY, "illustAC", 0xffffff);
	DrawString(480, 850 + g_PosY, "UTILITY-LABO", 0xffffff);
	DrawString(480, 950 + g_PosY, "BANNERKOUBOU", 0xffffff);
	DrawString(500, 1050 + g_PosY, "SE・BGMなど", 0xffffff);
	DrawString(472, 1150 + g_PosY, "DOVA-SYNDROME", 0xffffff);
	DrawString(510, 1250 + g_PosY, "ユーフルカ", 0xffffff);
	DrawString(513, 1350 + g_PosY, "効果音工房", 0xffffff);
	DrawString(513, 1450 + g_PosY, "効果音ラボ", 0xffffff);
	DrawString(510, 1550 + g_PosY, "関係者の方", 0xffffff);
	DrawString(270, 1650 + g_PosY, "グラフィックデザイン科の方々", 0xffffff);

	//DrawString(200, 350+g_PosY, "pngtree", 0xffffff);
	//DrawString(200, 470+g_PosY, "チコデザ", 0xffffff);
	//DrawString(200, 530+g_PosY, "ツカッテ", 0xffffff);
	//DrawString(200, 590+g_PosY, "BOOTH", 0xffffff);
	//DrawString(200, 650+g_PosY, "インディー8ビット", 0xffffff);
	//DrawString(200, 710+g_PosY, "AKKODiS", 0xffffff);
	//DrawString(200, 770+g_PosY, "romptnAI", 0xffffff);
	//DrawString(200, 830+g_PosY, "ITOTM", 0xffffff);
	//DrawString(200, 890+g_PosY, "くろくまそふと", 0xffffff);
	//DrawString(200, 950+g_PosY, "note_lilish", 0xffffff);
	//DrawString(200, 1010+g_PosY, "A.I. Art Stock", 0xffffff);
	//DrawString(200, 1070+g_PosY, "ドッタウン", 0xffffff);
	//DrawString(200, 1130+g_PosY, "ピクセルアートタウン", 0xffffff);
}
