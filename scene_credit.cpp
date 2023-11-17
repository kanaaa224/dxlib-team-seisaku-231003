#include "main.h"

Credit::Credit()
{
	//クレジット画像の読込
	CreditImage = LoadGraph("resources/images/background.png");
	//時間の初期化
	g_WaitTime = 0;
}

Credit::~Credit()
{

}

Scene* Credit::update()
{
	//クレジットロール処理
	//時間がたてばタイトルへ遷移
	if (++g_WaitTime < 1500)g_PosY = 600 - g_WaitTime;
	if (++g_WaitTime > 900) {
		return new Title;
	}
	return this;
}

void Credit::draw()const
{
	//クレジット画像の表示
	DrawExtendGraph(0, 0,1280,720, CreditImage, TRUE);
	//使ったサイトや関係者名の名前を表示
	SetFontSize(40);
	DrawString(100, 350+g_PosY, "pngtree", 0x000000);
	DrawString(100, 390+g_PosY, "グラフィックデザイン科の方々", 0x000000);
}
