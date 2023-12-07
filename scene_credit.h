#pragma once

#include "scene.h"

class Credit : public Scene
{
private:
	//画像読み込み用の変数
	int CreditImage;
	//クレジットロール用の変数
	int g_WaitTime;
	int g_PosY;

	int Credit_Mouse_x;
	int Credit_Mouse_y;

public:
	//コンストラクタ
	Credit();
	~Credit();
	//更新
	Scene* update()override;
	//描画
	void draw()const override;
};

